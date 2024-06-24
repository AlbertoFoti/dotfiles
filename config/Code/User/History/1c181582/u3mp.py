import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Define plot parameters
radius = 1
num_circles = 16  # Number of circles around the sphere
circle_radius = 0.8  # Radius of the circles

# Generate sphere points using theta and phi angles
theta_sphere, phi_sphere = np.mgrid[0.0:np.pi:50j, 0.0:2.0*np.pi:50j]
x_sphere = radius * np.sin(theta_sphere) * np.cos(phi_sphere)
y_sphere = radius * np.sin(theta_sphere) * np.sin(phi_sphere)
z_sphere = radius * np.cos(theta_sphere)

# Generate circle positions around the sphere
phi_circle = np.linspace(0, 2*np.pi, num_circles)  # Angles for circle placement
theta_circle = np.pi/2  # Constant theta for circles on a plane

# Calculate circle center coordinates (x, y, z) based on phi_circle
x_circle_center = radius * np.cos(phi_circle)
y_circle_center = radius * np.sin(phi_circle)
z_circle_center = 0  # Circles lie on the x-y plane

# Generate circle points around each center (offset for visibility)
circle_offset = 0.1  # Adjust offset to avoid clipping with sphere

def generate_circle_points(center_x, center_y, center_z, circle_radius):
  theta_circle_points = np.linspace(0, 2*np.pi, 20)  # Points for each circle
  x_circle = circle_radius * np.cos(theta_circle_points) + center_x + circle_offset
  y_circle = circle_radius * np.sin(theta_circle_points) + center_y + circle_offset
  z_circle = np.zeros_like(x_circle) + center_z  # All circles on z=0 plane
  return x_circle, y_circle, z_circle

# Create lists to store all circle points
x_circles = []
y_circles = []
z_circles = []

for i in range(num_circles):
  # Generate points for each circle and append to lists
  x, y, z = generate_circle_points(x_circle_center[i], y_circle_center[i], z_circle_center[i], circle_radius)
  x_circles.append(x)
  y_circles.append(y)
  z_circles.append(z)

# Create a new figure and a set of subplots
fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(111, projection='3d')

# Plot the sphere surface
ax.plot_trisurf(x_sphere, y_sphere, z_sphere, cmap='viridis', linewidth=0.2)

# Plot all the circles
for i in range(num_circles):
  ax.plot(x_circles[i], y_circles[i], z_circles[i], color='red', linewidth=1)  # Adjust color and line width

# Set labels and title
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Sphere with 16 Circles', fontsize=16)

# Set axis limits slightly bigger than sphere and circles
ax.set_xlim(-radius - circle_radius - circle_offset, radius + circle_radius + circle_offset)
ax.set_ylim(-radius - circle_radius - circle_offset, radius + circle_radius + circle_offset)
ax.set_zlim(-radius/5, radius/5)

# Set camera view (optional)
ax.view_init(elev=15, azim=-60)  # Adjust elevation and azimuth for desired view

plt.tight_layout()
plt.show()