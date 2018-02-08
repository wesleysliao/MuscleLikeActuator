;; Auto-generated. Do not edit!


(when (boundp 'tivac_iocontrol_msg::IO_Control)
  (if (not (find-package "TIVAC_IOCONTROL_MSG"))
    (make-package "TIVAC_IOCONTROL_MSG"))
  (shadow 'IO_Control (find-package "TIVAC_IOCONTROL_MSG")))
(unless (find-package "TIVAC_IOCONTROL_MSG::IO_CONTROL")
  (make-package "TIVAC_IOCONTROL_MSG::IO_CONTROL"))

(in-package "ROS")
;;//! \htmlinclude IO_Control.msg.html


(defclass tivac_iocontrol_msg::IO_Control
  :super ros::object
  :slots (_port _mask _value ))

(defmethod tivac_iocontrol_msg::IO_Control
  (:init
   (&key
    ((:port __port) 0)
    ((:mask __mask) 0)
    ((:value __value) 0)
    )
   (send-super :init)
   (setq _port (round __port))
   (setq _mask (round __mask))
   (setq _value (round __value))
   self)
  (:port
   (&optional __port)
   (if __port (setq _port __port)) _port)
  (:mask
   (&optional __mask)
   (if __mask (setq _mask __mask)) _mask)
  (:value
   (&optional __value)
   (if __value (setq _value __value)) _value)
  (:serialization-length
   ()
   (+
    ;; uint8 _port
    1
    ;; int8 _mask
    1
    ;; int8 _value
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _port
       (write-byte _port s)
     ;; int8 _mask
       (write-byte _mask s)
     ;; int8 _value
       (write-byte _value s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _port
     (setq _port (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; int8 _mask
     (setq _mask (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _mask 127) (setq _mask (- _mask 256)))
   ;; int8 _value
     (setq _value (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _value 127) (setq _value (- _value 256)))
   ;;
   self)
  )

(setf (get tivac_iocontrol_msg::IO_Control :md5sum-) "dc750dd0a815484a3bf3d6f436ecdc55")
(setf (get tivac_iocontrol_msg::IO_Control :datatype-) "tivac_iocontrol_msg/IO_Control")
(setf (get tivac_iocontrol_msg::IO_Control :definition-)
      "uint8 port
int8 mask
int8 value
")



(provide :tivac_iocontrol_msg/IO_Control "dc750dd0a815484a3bf3d6f436ecdc55")


