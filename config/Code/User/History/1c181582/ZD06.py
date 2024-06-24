import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Define plot parameters
radius = 1
circle_radius = 1.25  # Radius of the circle around the sphere
num_circle_points = 50  # Number of points for the circle

# Generate sphere points using theta and phi angles
theta, phi = np.mgrid[0.0:np.pi:50j, 0.0:2.0*np.pi:50j]
x_sphere = radius * np.sin(theta) * np.cos(phi)
y_sphere = radius * np.sin(theta) * np.sin(phi)
z_sphere = radius * np.cos(theta)

# Generate circle points around the sphere (x, y plane)
theta_circle = np.linspace(0, 2*np.pi, num_circle_points)
x_circle = circle_radius * np.cos( theta_circle )
y_circle = circle_radius * np.sin( theta_circle )

# Create a new figure and a set of subplots
fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(111, projection='3d')

# Plot the sphere surface
ax.plot_trisurf(x_sphere.flatten(), y_sphere.flatten(), z_sphere.flatten(), cmap='viridis', linewidth=0.2)

# Plot the circle around the sphere (x, y plane, z=0)
ax.plot(x_circle, y_circle, 0, color='red', linewidth=2)  # Adjust color and line width

# Set labels and title with desired positions
ax.text(-radius - radius/5, radius + radius/5, 0, 'X', fontsize=14, ha='center')
ax.text(radius + radius/5, 0, 0, 'Y', fontsize=14, ha='center')
ax.text(0, 0, radius + radius/5, 'Z', fontsize=14, va='center')
ax.set_title('Sphere with Circle and Axis Labels', fontsize=16)

# Set axis limits slightly bigger than sphere and circle
ax.set_xlim(-radius - circle_radius/2, radius + circle_radius/2)
ax.set_ylim(-radius - circle_radius/2, radius + circle_radius/2)
ax.set_zlim(-radius - radius/5, radius + radius/5)

# Set camera view (optional)
ax.view_init(elev=15, azim=-60)  # Adjust elevation and azimuth for desired view

plt.tight_layout()
plt.show()