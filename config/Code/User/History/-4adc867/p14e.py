import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Define arrow properties
arrow_length = 1.0
head_width = 0.2  # fraction of arrow length
head_length = 0.3  # fraction of arrow length

# Generate animation frames (replace with loop for real-time simulation)
num_frames = 100
angles = np.linspace(0, 2*np.pi, num_frames)  # Angles for each frame

# Setup 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlim3d(-arrow_length, arrow_length)
ax.set_ylim3d(-arrow_length, arrow_length)
ax.set_zlim3d(-arrow_length, arrow_length)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Rotating Vector (3D)')

# Create arrow object
line, = ax.plot([0], [0], [0], '->', ms=10, mew=2, color='blue')

for i, angle in enumerate(angles):
  # Calculate head and tail coordinates based on angle and arrow properties
  x_tail = 0
  y_tail = 0
  z_tail = 0
  x_head = x_tail + arrow_length * np.cos(angle)
  y_head = y_tail + arrow_length * np.sin(angle)
  z_head = 0  # Fixed Z-coordinate for in-plane rotation

  # Update arrow data with new coordinates
  line.set_data([x_tail, x_head], [y_tail, y_head], [z_tail, z_head])

  # Clear the figure to simulate animation (optional for smoother display)
  plt.cla()

  # Optionally, add a small pause between frames for a slower "animation"
  # plt.pause(0.01)  # Adjust pause time for desired speed

# Display the final plot (or uncomment pause for frame-by-frame viewing)
plt.show()