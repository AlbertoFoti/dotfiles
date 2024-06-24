def spherical_to_cartesian(radius, lon, lat):
    x = radius * np.cos(lon) * np.cos(lat)
    y = radius * np.sin(lon) * np.cos(lat)
    z = radius * np.sin(lat)
    return x, y, z

# Define the coordinates and orientation
coords = {
    "r": 2.00,
    "lon": 0.50,
    "lat": 45.00,
    "fpa": 0.00,
    "head": 0.00
}

# Define the spherical coordinates and orientation
radius = 2.00
lon = 0.50
lat = 45.00
fpa = 0.00
head = 0.00

# Convert spherical coordinates to Cartesian coordinates
x, y, z = spherical_to_cartesian(radius, lon, lat)

# Define sphere properties
radius = 1
center = (0, 0, 0)

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the sphere
u = np.linspace(0, 2 * np.pi, 100)
v = np.linspace(0, np.pi, 100)
x = center[0] + radius * np.outer(np.cos(u), np.sin(v))
y = center[1] + radius * np.outer(np.sin(u), np.sin(v))
z = center[2] + radius * np.outer(np.ones(np.size(u)), np.cos(v))
ax.plot_surface(x, y, z, color='b', alpha=0.2)

# Plot the object
ax.scatter(coords['x'], coords['y'], coords['z'], color='r', label='Object')

# Plot orientation
arrow_length = 0.5
ax.quiver(coords['x'], coords['y'], coords['z'],
          np.sin(coords['head']) * np.cos(coords['fpa']) * arrow_length,
          np.cos(coords['head']) * np.cos(coords['fpa']) * arrow_length,
          np.sin(coords['fpa']) * arrow_length, color='g', label='Orientation')

# Set labels and title
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Plot with Sphere and Object')

# Set equal aspect ratio
ax.set_box_aspect([1,1,1])

# Show legend
ax.legend()

# Show the plot
plt.show()