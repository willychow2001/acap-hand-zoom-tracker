/* Main loop: detection, tracking, zoom logic */

#include "person_tracker.h"
#include "hand_detector.h"
#include "zoom_controller.h"
#include "utils.h"

int main() {
    init_person_tracker("models/person_detection.larod");
    init_hand_detector("models/hand_detection.larod");
    init_zoom_controller();

    while (1) {
        Person p = detect_target_person();
        if (p.found) {
            if (is_stationary(p, STOP_TIME_THRESHOLD)) {
                HandRegion h = detect_hands(p);
                if (h.found) {
                    zoom_to_region(h.bbox);
                }
            }
        }
        sleep_ms(100);
    }

    cleanup();
    return 0;
}