import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

pi = 3.1416

def spherical_to_cartesian(radius, lon, lat):
    x = radius * np.cos(lon) * np.cos(lat)
    y = radius * np.sin(lon) * np.cos(lat)
    z = radius * np.sin(lat)
    return x, y, z

# Define the coordinates and orientation
coords = {
    "r": 3516200.00,
    "lon": -0.6614798*180/pi,
    "lat": 0.3708825*180/pi,
    "fpa": -0.2268928*180/pi,
    "head": 1.7597*180/pi
}

# Define the spherical coordinates and orientation
eip_radius = 3516200.00
eip_lon = 0.00
eip_lat = 45.00
eip_fpa = 0.00
eip_head = 0.00

# Convert spherical coordinates to Cartesian coordinates
eip_x, eip_y, eip_z = spherical_to_cartesian(eip_radius, eip_lon, eip_lat)

target_radius = 3400000.00
target_lat = 0.3169343389*180/pi
target_lon = -0.4247084202*180/pi
# Convert spherical coordinates to Cartesian coordinates
target_x, target_y, target_z = spherical_to_cartesian(target_radius, target_lat, target_lon)

# Define sphere properties
radius = 3400000
center = (0, 0, 0)

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the object
ax.scatter(eip_x, eip_y, eip_z, color='g', label='Lander')
ax.scatter(target_x, target_y, target_z, color='r', label='Oxia Planum (LS)')

# Plot the sphere
u = np.linspace(0, 2 * np.pi, 100)
v = np.linspace(0, np.pi, 100)
x = center[0] + radius * np.outer(np.cos(u), np.sin(v))
y = center[1] + radius * np.outer(np.sin(u), np.sin(v))
z = center[2] + radius * np.outer(np.ones(np.size(u)), np.cos(v))
ax.plot_surface(x, y, z, color='b', alpha=0.2)

# Plot orientation
arrow_length = 500000
ax.quiver(eip_x, eip_y, eip_z,
          np.sin(eip_head) * np.cos(eip_fpa) * arrow_length,
          np.cos(eip_head) * np.cos(eip_fpa) * arrow_length,
          np.sin(eip_fpa) * arrow_length, color='g', label='Orientation')

# Set labels and title
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Nominal trajectory simulation')

# Set equal aspect ratio
ax.set_box_aspect([1,1,1])

# Manually set axis limits
ax.set_xlim([-4000000, 4000000])
ax.set_ylim([-4000000, 4000000])
ax.set_zlim([-4000000, 4000000])

# Show legend
ax.legend()

# Show the plot
plt.show()