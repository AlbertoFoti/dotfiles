import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Define sphere radius
radius = 1

# Create a new figure and a set of subplots
fig = plt.figure(figsize=(8, 8))
ax = fig.add_subplot(111, projection='3d')

# Generate sphere points using theta and phi angles
theta, phi = np.mgrid[0.0:np.pi:50j, 0.0:2.0*np.pi:50j]
x = radius * np.sin(theta) * np.cos(phi)
y = radius * np.sin(theta) * np.sin(phi)
z = radius * np.cos(theta)

# Plot the sphere surface
ax.plot_trisurf(x, y, z, cmap='viridis', linewidth=0.2)  # Adjust colormap as desired

# Set labels and title
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Sphere')

# Set axis limits slightly bigger than radius
ax.set_xlim(-radius - radius/5, radius + radius/5)
ax.set_ylim(-radius - radius/5, radius + radius/5)
ax.set_zlim(-radius - radius/5, radius + radius/5)

# Set camera view (optional)
ax.view_init(elev=15, azim=-60)  # Adjust elevation and azimuth for desired view

plt.tight_layout()
plt.show()