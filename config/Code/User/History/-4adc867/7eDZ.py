import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Define arrow properties
arrow_length = 1.0
head_width = 0.2  # fraction of arrow length
head_length = 0.3  # fraction of arrow length

# Generate animation frames (replace with loop for real-time simulation)
num_frames = 10000

# r = np.genfromtxt("r_profile.txt", delimiter="\n")
# lat = np.genfromtxt("lat_profile.txt", delimiter="\n")
# lon = np.genfromtxt("lon_profile.txt", delimiter="\n")

# Setup 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.view_init(elev=35, azim=45)
ax.set_box_aspect([1, 1, 1])


    ax.clear()

    ax.quiver(0, 0, 0, 1, 0, 0, color='green')
    ax.quiver(0, 0, 0, 0, 1, 0, color='green')
    ax.quiver(0, 0, 0, 0, 0, 1, color='red')

    ax.set_xlim(-5, 5)
    ax.set_ylim(-5, 5)
    ax.set_zlim(-5, 5)


    # Optionally, add a small pause between frames for a slower "animation"
    plt.draw()
    plt.pause(0.001)  # Adjust pause time for desired speed