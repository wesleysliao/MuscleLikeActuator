; Auto-generated. Do not edit!


(cl:in-package tivac_iocontrol_msg-msg)


;//! \htmlinclude IO_Control.msg.html

(cl:defclass <IO_Control> (roslisp-msg-protocol:ros-message)
  ((port
    :reader port
    :initarg :port
    :type cl:fixnum
    :initform 0)
   (mask
    :reader mask
    :initarg :mask
    :type cl:fixnum
    :initform 0)
   (value
    :reader value
    :initarg :value
    :type cl:fixnum
    :initform 0))
)

(cl:defclass IO_Control (<IO_Control>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <IO_Control>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'IO_Control)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name tivac_iocontrol_msg-msg:<IO_Control> is deprecated: use tivac_iocontrol_msg-msg:IO_Control instead.")))

(cl:ensure-generic-function 'port-val :lambda-list '(m))
(cl:defmethod port-val ((m <IO_Control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader tivac_iocontrol_msg-msg:port-val is deprecated.  Use tivac_iocontrol_msg-msg:port instead.")
  (port m))

(cl:ensure-generic-function 'mask-val :lambda-list '(m))
(cl:defmethod mask-val ((m <IO_Control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader tivac_iocontrol_msg-msg:mask-val is deprecated.  Use tivac_iocontrol_msg-msg:mask instead.")
  (mask m))

(cl:ensure-generic-function 'value-val :lambda-list '(m))
(cl:defmethod value-val ((m <IO_Control>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader tivac_iocontrol_msg-msg:value-val is deprecated.  Use tivac_iocontrol_msg-msg:value instead.")
  (value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <IO_Control>) ostream)
  "Serializes a message object of type '<IO_Control>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'port)) ostream)
  (cl:let* ((signed (cl:slot-value msg 'mask)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'value)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <IO_Control>) istream)
  "Deserializes a message object of type '<IO_Control>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'port)) (cl:read-byte istream))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mask) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'value) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<IO_Control>)))
  "Returns string type for a message object of type '<IO_Control>"
  "tivac_iocontrol_msg/IO_Control")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'IO_Control)))
  "Returns string type for a message object of type 'IO_Control"
  "tivac_iocontrol_msg/IO_Control")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<IO_Control>)))
  "Returns md5sum for a message object of type '<IO_Control>"
  "dc750dd0a815484a3bf3d6f436ecdc55")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'IO_Control)))
  "Returns md5sum for a message object of type 'IO_Control"
  "dc750dd0a815484a3bf3d6f436ecdc55")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<IO_Control>)))
  "Returns full string definition for message of type '<IO_Control>"
  (cl:format cl:nil "uint8 port~%int8 mask~%int8 value~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'IO_Control)))
  "Returns full string definition for message of type 'IO_Control"
  (cl:format cl:nil "uint8 port~%int8 mask~%int8 value~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <IO_Control>))
  (cl:+ 0
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <IO_Control>))
  "Converts a ROS message object to a list"
  (cl:list 'IO_Control
    (cl:cons ':port (port msg))
    (cl:cons ':mask (mask msg))
    (cl:cons ':value (value msg))
))
