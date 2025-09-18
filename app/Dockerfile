# Start from the ACAP Native SDK image you already pulled
FROM axisecp/acap-native-sdk:12.5.0-aarch64-ubuntu24.04

# Set working directory inside the container
WORKDIR /opt/app

# Copy your application source into the container
COPY app/ /opt/app/

# Build the application
RUN make

# Default command (not really used for ACAP builds)
CMD ["/bin/bash"]