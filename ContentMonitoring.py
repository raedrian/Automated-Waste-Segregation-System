import orangepi.GPIO as GPIO  # Replace with your appropriate library
import serial
import time

# Sensor configuration
NUM_SENSORS = 4
trigPins = [2, 4, 6, 8]
echoPins = [3, 5, 7, 9]
ledPins = [22, 23, 24, 25]

def read_sonar_sensor(sensor_trig_pin, sensor_echo_pin):
  # Send ultrasonic ping
  GPIO.output(sensor_trig_pin, False)
  time.sleep(0.000002)  # Adjusted delay for microseconds
  GPIO.output(sensor_trig_pin, True)
  time.sleep(0.00001)  # Adjusted delay for microseconds
  GPIO.output(sensor_trig_pin, False)

  # Read echo pulse
  pulse_start = time.time()
  while GPIO.input(sensor_echo_pin) == 0:
    pass
  while GPIO.input(sensor_echo_pin) == 1:
    pass
  pulse_end = time.time()

  # Calculate distance
  pulse_duration = pulse_end - pulse_start
  distance = pulse_duration * 34300 / 2

  # Control LED based on distance
  if distance >= 18 or distance == 0:
    GPIO.output(ledPins[sensor_trig_pin.index(sensor_trig_pin)], GPIO.LOW)
  else:
    GPIO.output(ledPins[sensor_trig_pin.index(sensor_trig_pin)], GPIO.HIGH)

  return distance

def main():
  # Setup GPIO pins
  GPIO.setmode(GPIO.BCM)
  for sensor in range(NUM_SENSORS):
    GPIO.setup(trigPins[sensor], GPIO.OUT)
    GPIO.setup(echoPins[sensor], GPIO.IN)
    GPIO.setup(ledPins[sensor], GPIO.OUT)

  # Setup serial communication
  ser = serial.Serial('/dev/ttyUSB0', 9600)  # Adjust port name if needed

  try:
    while True:
      distances = []
      for sensor in range(NUM_SENSORS):
        distances.append(read_sonar_sensor(trigPins[sensor], echoPins[sensor]))

      # Print sensor distances
      ser.write(" ".join([str(d) for d in distances]) + "\n".encode('utf-8'))
      time.sleep(0.025)  # Delay between readings

  except KeyboardInterrupt:
    pass  # Handle exiting the program with Ctrl+C

  finally:
    # Cleanup GPIO pins
    GPIO.cleanup()

if __name__ == "__main__":
  main()
