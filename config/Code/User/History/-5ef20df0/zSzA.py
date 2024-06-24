import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from descentModule import DescentModule
#from stl import mesh
from numpy import cos, sin

# Function to apply rotation
def rotate(vec, heading, fpa):
    # Rotation matrix for heading (z-axis)
    R_heading = np.array([[np.cos(-heading), -np.sin(-heading), 0],
                       [np.sin(-heading), np.cos(-heading), 0],
                       [0, 0, 1]])
    
    # Rotation matrix for FPA (y-axis)
    R_fpa = np.array([[np.cos(fpa), 0, np.sin(fpa)],
                        [0, 1, 0],
                        [-np.sin(fpa), 0, np.cos(fpa)]])
    R = np.dot(R_heading, R_fpa)

    return np.dot(vec, R.T)


# Function to plot a wireframe sphere
def plot_wireframe_sphere(ax, x0, y0, z0, radius=1, color='b', alpha=0.2):
    # Create a grid of points in spherical coordinates
    u = np.linspace(0, 2 * np.pi, 100)
    v = np.linspace(0, np.pi, 50)
    x = x0 + radius * np.outer(np.cos(u), np.sin(v))
    y = y0 + radius * np.outer(np.sin(u), np.sin(v))
    z = z0 + radius * np.outer(np.ones(np.size(u)), np.cos(v))
    
    # Plot the wireframe
    ax.plot_wireframe(x, y, z, color=color, alpha=alpha)

# Function to plot a wireframe sphere in spherical coordinates
def plot_wireframe_sphere_spherical(ax, r, lon, lat, radius=1, color='b', alpha=0.2):
    x0 = r*cos(lat)*cos(lon)
    y0 = r*cos(lat)*sin(lon)
    z0 = r*sin(lat)

    # Create a grid of points in spherical coordinates
    u = np.linspace(0, 2 * np.pi, 100)
    v = np.linspace(0, np.pi, 50)
    x = x0 + radius * np.outer(np.cos(u), np.sin(v))
    y = y0 + radius * np.outer(np.sin(u), np.sin(v))
    z = z0 + radius * np.outer(np.ones(np.size(u)), np.cos(v))
    
    # Plot the wireframe
    ax.plot_wireframe(x, y, z, color=color, alpha=alpha)

dm = DescentModule()

# Initialize the figure and 3D axes
fig = plt.figure(figsize=(15, 10))
gs = fig.add_gridspec(4, 4)

ax = fig.add_subplot(gs[0:2, 2:4], projection='3d')
ax.view_init(elev=35, azim=-120)  # Adjust these for desired view
ax.set_box_aspect([1, 1, 1])

# Read data from file
r = np.genfromtxt("r_profile.txt", delimiter="\n")
lat = np.genfromtxt("lat_profile.txt", delimiter="\n")
lon = np.genfromtxt("lon_profile.txt", delimiter="\n")
vel = np.genfromtxt("vel_profile.txt", delimiter="\n")
N = len(vel)
heading = np.genfromtxt("head_profile.txt", delimiter="\n")
fpa = np.genfromtxt("fpa_profile.txt", delimiter="\n")
bank = np.genfromtxt("mu_profile.txt", delimiter="\n")

zero_heading = np.zeros(N)
zero_fpa = np.zeros(N)
zero_bank = np.zeros(N)

# 2D subplot for real-time data
ax2 = fig.add_subplot(gs[2:4, 2]) 
ax2.set_xlim([0, N])
ax2.set_ylim([min(bank), max(bank)])
x_data, y_data = [], []
line2, = ax2.plot([], [], 'r-')

ax3 = fig.add_subplot(gs[0:4, 0:2], projection='3d')
ax3.view_init(elev=15, azim=-60)
ax3.grid(True)

ax4 = fig.add_subplot(gs[2:4, 3])
ax4.set_xlim([0, N])
ax4.set_ylim([0, max(vel)+100])
x_data4, y_data4 = [], []
line4, = ax4.plot([], [], 'k-')

t = 0

while t < 290:
    # Clear the plot for a fresh render
    ax.clear()
    ax3.clear()

    dm.updatePosition(r[t], lon[t], lat[t])

    dm.updateAttitude(heading[t], fpa[t], bank[t])

    dm.plot(ax)
    dm.plotAtOrigin(ax3)

    # Plot an empty sphere in the second 3D subplot
    plot_wireframe_sphere(ax, 0, 0, 120, radius=3389000, color='r', alpha=0.2)
    # Plot EIP
    r_eip = 3516200.00
    lon_eip = -0.6614798
    lat_eip = 0.3708825
    plot_wireframe_sphere_spherical(ax, r_eip, lon_eip, lat_eip, radius=5000, color='g', alpha=0.2)
    # Plot PDP (nominal)
    r_pdp = 0
    lon_pdp = 0
    lat_pdp = 0
    plot_wireframe_sphere_spherical(ax, r_pdp, lon_pdp, lat_pdp, radius=5000, color='b', alpha=0.2)

    # Plot the NED ref. frame
    ax3.quiver(-17, -17, 0, 5, 0, 0, color='green')    
    ax3.quiver(-17, -17, 0, 0, -5, 0, color='orange')    
    ax3.quiver(-17, -17, 0, 0, 0, -5, color='red')    

    # Plot the velocity vector
    vel_vectorx = rotate([20, 0, 0], heading[t], fpa[t])
    ax3.quiver(0, 0, 0, vel_vectorx[0], vel_vectorx[1], vel_vectorx[2], color='green')
    vel_vectory = rotate([0, -10, 0], heading[t], fpa[t])
    ax3.quiver(0, 0, 0, vel_vectory[0], vel_vectory[1], vel_vectory[2], color='orange')
    vel_vectorz = rotate([0, 0, -10], heading[t], fpa[t])
    ax3.quiver(0, 0, 0, vel_vectorz[0], vel_vectorz[1], vel_vectorz[2], color='red')

    # Set axis limits for all three axes (X, Y, Z)
    #ax.set_xlim(-r[0]-10000, r[0]+10000)
    ax.set_xlim(2000000, 4000000)
    #ax.set_ylim(-r[0]-10000, r[0]+10000)
    ax.set_ylim(-3000000, -1000000)
    #ax.set_zlim(-r[0]-10000, r[0]+10000)
    ax.set_zlim(0, 2000000)

    ax3.set_xlim([-20, 20])
    ax3.set_ylim([-20, 20])
    ax3.set_zlim([-20, 20])

    # Update rotation angle
    #theta += 0.1  # Adjust for desired rotation speed

    # Update the 2D subplot
    x_data.append(t)
    y_data.append(bank[t])  # Random data for demonstration
    line2.set_data(x_data, y_data)

    x_data4.append(t)
    y_data4.append(vel[t])
    line4.set_data(x_data4, y_data4)
    
    ax2.set_ylim([min(bank)-1, max(bank)+1])  # Keep y-axis fixed between 0 and 100
    ax2.grid(True)

    ax4.set_ylim([min(vel)-100, max(vel)+100])  # Keep y-axis fixed between 0 and 100
    ax4.grid(True)

    # Render the plot and pause for a smooth animation
    t += 1
    plt.draw()
    plt.pause(0.01)