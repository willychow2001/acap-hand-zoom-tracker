/* Main loop: detection, tracking, zoom logic */

#include <signal.h>
#include <stdbool.h>
#include <syslog.h>
#include <unistd.h>
#include "person_tracker.h"
#include "hand_detector.h"
#include "zoom_controller.h"
#include "utils.h"

#define APP_NAME "acap-hand-zoom"
#define STOP_TIME_THRESHOLD 2000 // ms

static volatile bool keep_running = true;

static void handle_signal(int sig) {
    syslog(LOG_INFO, "Signal %d received, shutting down...", sig);
    keep_running = false;
}

int main(void) {
    // Open syslog for logging
    openlog(APP_NAME, LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Starting %s application", APP_NAME);

    // Register signal handlers
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    // Initialize components
    if (!init_person_tracker("/usr/local/packages/acap-hand-zoom/models/person_detection.larod")) {
        syslog(LOG_ERR, "Failed to initialize person tracker");
        return 1;
    }
    if (!init_hand_detector("/usr/local/packages/acap-hand-zoom/models/hand_detection.larod")) {
        syslog(LOG_ERR, "Failed to initialize hand detector");
        return 1;
    }
    if (!init_zoom_controller()) {
        syslog(LOG_ERR, "Failed to initialize zoom controller");
        return 1;
    }

    // Main loop
    while (keep_running) {
        Person p = detect_target_person();
        if (p.found && is_stationary(p, STOP_TIME_THRESHOLD)) {
            HandRegion h = detect_hands(p);
            if (h.found) {
                zoom_to_region(h.bbox);
            }
        }
        sleep_ms(100);
    }

    // Cleanup
    cleanup();
    syslog(LOG_INFO, "Application stopped");
    closelog();
    return 0;
}