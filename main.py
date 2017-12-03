
import numpy as np
import matplotlib.pyplot as plt
import scipy
import scipy.integrate
import scipy.stats
from operator import itemgetter

def armmodel(t, y, force):
	theta = y[0]
	thetad = y[1]

	g = 9.81; #meters per second^2

	r = 0.1; #meters
	d = 0.01; #meters
	m = .1; #kilograms
	k = 10; #N/m
	Io = (m*(r*r))/2; 

	thetadd = ((force*r)-(k*r*r*theta)-(d*m*g*np.cos(theta)))/Io
	return [thetad, thetadd]

class ActuatorModel:
	def __init__(self, nominalForce, actuationVariance):
		self.functional = True
		self.nominalForce = nominalForce
		self.actuationVariance = actuationVariance
		self.activated = False
		self.activations = 0
		self.suspicion = 0
		self.force = 0

	def actuationForce(self):
		return self.nominalForce

	def activate(self):
		if not self.activated:
			if self.functional:
				self.force = self.actuationForce()
			else:
				self.force = 0
			self.activations += 1
			self.activated = True
			return self.force

	def deactivate(self):
		if self.activated:
			self.force = 0
			self.activated = False

class SingleActuator(ActuatorModel):
	def __init__(self, nominalForce, forceVariance, actuationVariance):
		if forceVariance <= 0:
			self.actualForce = nominalForce
		else:
			self.actualForce = np.random.normal(nominalForce, np.sqrt(forceVariance))
		super().__init__(nominalForce, actuationVariance)

	def actuationForce(self):
		return max(np.random.normal(self.actualForce, np.sqrt(self.actuationVariance)),0)

class Muscle:
	def __init__(self, nominalForces, actuationVariances):
		self.actuators = {}
		for actuator in range(len(nominalForces)):
			self.actuators[len(self.actuators)] = SingleActuator(nominalForces[actuator], 0, actuationVariances[actuator])

	def force(self):
		totalforce = 0
		for actuator in self.actuators.values():
			totalforce += actuator.force

		return totalforce

	def nominalForce(self):
		totalforce = 0
		for actuator in self.actuators.values():
			if actuator.activated and actuator.functional:
				totalforce += actuator.nominalForce

		return totalforce

	def command(self, activatedIDs):
		for key, value in self.actuators.items():
			if key in activatedIDs:
				self.actuators[key].activate()
			else:
				self.actuators[key].deactivate()
		return self.force()

class MusclePredictor(Muscle):
	def __init__(self, muscle, failedIDs):
		self.actuators = {}
		for key, value in muscle.actuators.items():
			self.actuators[key] = ActuatorModel(value.nominalForce, value.actuationVariance)
			for ID in failedIDs:
				if key == ID:
					self.actuators[key].functional = False

	def likelyhood(self, command, resultingForce):

		self.command(command)

		mean=0
		variance = 0
		for actuator in self.actuators.values():
			if actuator.activated and actuator.functional:
				variance += actuator.actuationVariance
				mean+= actuator.force

		if variance <= 0:
			return 1

		stdDev = np.sqrt(variance)

		z = (resultingForce - mean)/stdDev

		if z<0:
			return (scipy.stats.norm.cdf(z) + (1 - scipy.stats.norm.cdf(-z)))
		else:
			return (1 - scipy.stats.norm.cdf(z) + scipy.stats.norm.cdf(-z))



class Observer:
	def __init__(self, muscle, simultPredictors, historicalWeight):
		self.predictors = []
		self.histWeight = historicalWeight
		self.actuatorkeys = muscle.actuators.keys()

		if simultPredictors > len(self.actuatorkeys):
			simultPredictors = len(self.actuatorkeys)
		self.simultPredictors = simultPredictors

		for loop in range(self.simultPredictors):
			self.addPredictor(muscle)

	def predictorAlreadyExists(self, key):
		for predictor in self.predictors:
			if predictor[1].actuators[key].functional == False:
				return True
		return False

	def addPredictor(self, muscle):
		while True:
			badactuatorkey = np.random.randint(0, len(self.actuatorkeys))
			if not self.predictorAlreadyExists(badactuatorkey):
				self.predictors.append([badactuatorkey, MusclePredictor(muscle, [badactuatorkey]), 0.01])
				break

	def update(self, command, actualForce, muscle, threshold, reduction, method):
		for predictor in self.predictors:
			predictor[2] = ((self.histWeight-1)*(predictor[2]/self.histWeight)) + (predictor[1].likelyhood(command, actualForce)/self.histWeight)

		likelyhoods = [predictor[2] for predictor in self.predictors]
		average = np.mean(likelyhoods)
		stdDev = np.std(likelyhoods)

		for predictor in self.predictors:

			test = 0
			if method == "direct":
				test = predictor[2]
			elif method == "average":
				test = predictor[2]/average
			else: #method == "zvalue"
				if stdDev!=0:
					test = abs(average - predictor[2])/stdDev

			if test > threshold:#and (predictor[2]/average)>1.1:#abs(average-predictor[2]) > 1.5*stdDev:
				# print(self.predictors.index(predictor), " is SUSPICIOUS", [(act[0],act[1].functional) for act in predictor[1].actuators.items()])

				for predictor2 in self.predictors:
					predictor2[2]/=reduction
					muscle.actuators[predictor2[0]].suspicion -= .25

				# if muscle.actuators[predictor[0]].suspicion < 2:
				muscle.actuators[predictor[0]].suspicion += 1

				self.predictors.sort(key= itemgetter(2), reverse = True)
				muscle.actuators[self.predictors[-1][0]].suspicion = 0
				self.predictors = self.predictors[:-1]

				self.addPredictor(muscle)
				return



def quantizeClosest(desiredForce, Muscle):
	quantizedForce = 0

	unusedPool = [(actuator[0], actuator[1].nominalForce, actuator[1].activations, actuator[1].suspicion) for actuator in Muscle.actuators.items()]
	
	unusedPool.sort(key = itemgetter(3), reverse = True)
	unusedPool.sort(key = itemgetter(2), reverse = False)
	unusedPool.sort(key = itemgetter(1), reverse = True)
	usedPool = []

	# print(sorted([(item[0], item[3]) for item in unusedPool], key= itemgetter(1), reverse = True)[0])

	# print(unusedPool)

	
	while(True):
		difference = abs((quantizedForce)-desiredForce)
		bestCandidate = None
		for actuator in unusedPool:
			# print(bestCandidate, difference, (quantizedForce + actuator[1])-desiredForce)
			if (quantizedForce + actuator[1])-desiredForce < difference:
				difference = abs((quantizedForce + actuator[1])-desiredForce)
				bestCandidate = actuator
		if bestCandidate != None:
			unusedPool.remove(bestCandidate)
			usedPool.append(bestCandidate)
			quantizedForce+=bestCandidate[1]
		else:
			break

	return [actuator[0] for actuator in usedPool]


for metametaloop in range(1):

	testmethod = "average"

	threshold = 	[1.3]
	reduction =		[2]

	thresh = threshold[metametaloop]
	reduct = reduction[0]

	metasuccess = np.zeros(1)
	for metaloop in range(1):

		timelength = 10
		timestep = 0.01


		P = 5
		D = 0
		I = 0.2

		theta = np.zeros( (2, int(timelength/timestep)) )
		t = np.linspace(0, timelength, int(timelength/timestep) )

		muscleforce = np.zeros( int(timelength/timestep) )
		musclecommand = np.zeros( int(timelength/timestep) )
		error = np.zeros( int(timelength/timestep) )
		command = np.zeros( int(timelength/timestep) )
		response = np.zeros( int(timelength/timestep) )

		likelyhoods = np.zeros( (4, int(timelength/timestep)))

		suspicion = np.zeros( (12, int(timelength/timestep)))


		ierror = 0.0


		a = Muscle([.123, .123, .24, .24, .123, .123, .24, .24, .123, .123, .24, .24], [0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001,0.0001])

		a.actuators[2].functional = False

		# print([(act[0],act[1].functional) for act in a.actuators.items()])


		obs = Observer(a, 4, 100)


		r = scipy.integrate.ode(armmodel).set_integrator('dopri5')


		for step in range(1, int(timelength/timestep), 1):

			command[step] = (np.sin(t[step])+1)/2
			
			error[step] = command[step]-theta[0,step-1]
			ierror = ierror+error[step]
			derror = command[step]-theta[1,step-1]
		    
			response[step] = (P*error[step])+(I*ierror)+(D*derror)
			activate = quantizeClosest(max(response[step],0), a)
			muscleforce[step] = a.command(activate)


			obs.update(activate, muscleforce[step] , a, thresh, reduct, testmethod)

			average = np.mean([predictor[2] for predictor in obs.predictors])
			stdDev = np.std([predictor[2] for predictor in obs.predictors])
			likelyhoods[0][step] = (obs.predictors[0][2]/average)#abs(average-obs.predictors[0][2])/stdDev
			likelyhoods[1][step] = (obs.predictors[1][2]/average)#abs(average-obs.predictors[1][2])/stdDev
			likelyhoods[2][step] = (obs.predictors[2][2]/average)#abs(average-obs.predictors[2][2])/stdDev
			likelyhoods[3][step] = (obs.predictors[3][2]/average)#abs(average-obs.predictors[3][2])/stdDev

			for row in range(len(suspicion)):
				suspicion[row][step] = a.actuators[row].suspicion


			musclecommand[step] =  a.nominalForce()

			r.set_initial_value([theta[0,step],theta[1,step-1]],t[step-1])
			r.set_f_params(muscleforce[step])
			y = r.integrate(t[step])
			theta[0, step] = y[0]
			theta[1, step] = y[1]

		if	sorted([(actuator[0], actuator[1].suspicion) for actuator in a.actuators.items()], key= itemgetter(1), reverse = True)[0][0] == 2:
			metasuccess[metaloop] = 1
	print(metametaloop, testmethod, thresh, reduct, np.mean(metasuccess))


	plt.figure(0)
	plt.plot(t, command, label="command")
	plt.plot(t, error, label="error")
	plt.plot(t, response, label="response")
	plt.plot(t, muscleforce, label="muscleforce")
	plt.plot(t, musclecommand, label="musclecommand")
	plt.plot(t, theta[0,:], label="theta")
	plt.legend()

	plt.figure(1)
	plt.plot(t, likelyhoods[0], label="0")
	plt.plot(t, likelyhoods[1], label="1")
	plt.plot(t, likelyhoods[2], label="2")
	plt.plot(t, likelyhoods[3], label="3")
	plt.legend()

	plt.figure(2)
	lol = 0
	for suspect in suspicion:
		plt.plot(t, suspect, label=str(lol))
		lol+=1
	plt.legend()

	plt.show()