acap-hand-zoom/
│
├── app/
│   ├── src/
│   │   ├── main.c                # Main loop: detection, tracking, zoom logic
│   │   ├── person_tracker.c      # Person detection & ID matching
│   │   ├── hand_detector.c       # Hand detection using Larod
│   │   ├── zoom_controller.c     # PTZ control via VAPIX
│   │   └── utils.c               # Helper functions (timers, bounding box math)
│   │
│   ├── include/
│   │   ├── person_tracker.h
│   │   ├── hand_detector.h
│   │   ├── zoom_controller.h
│   │   └── utils.h
│   │
│   ├── manifest.json             # ACAP app metadata
│   ├── Makefile                  # Build instructions
│   ├── Dockerfile                # ACAP SDK build container
│   └── LICENSE
│
├── models/
│   ├── person_detection.larod    # Pre-trained person detection model
│   └── hand_detection.larod      # Pre-trained hand detection model
│
└── README.md