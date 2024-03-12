import cv2
from ultralytics import YOLO
import time


# Load the YOLOv8 model
model = YOLO('D:/PycharmProjects/AutomaticWasteSegregation/.venv/weights/best.pt')

# Open the video file
video_path = 0
cap = cv2.VideoCapture(video_path)

# Loop through the video frames
while cap.isOpened():
    time.sleep(1)
    # Read a frame from the video
    success, frame = cap.read()

    if success:
        # Run YOLOv8 inference on the frame
        results = model(frame, verbose=False, conf = 0.4)
        names = model.names

        for r in results:
            for c in r.boxes.cls:
                label = names[int(c)]
                print(label)

        # Visualize the results on the frame
        annotated_frame = results[0].plot()

        # Display the annotated frame
        cv2.imshow("YOLOv8 Inference", annotated_frame)

        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
    else:
        # Break the loop if the end of the video is reached
        break

# Release the video capture object and close the display window
cap.release()
cv2.destroyAllWindows()
