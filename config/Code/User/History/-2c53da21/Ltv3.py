import numpy as np
from numpy import sin, cos

# Function to apply rotation
def rotate(vertices, heading, fpa, bank):
    # Rotation matrix for heading (z-axis)
    R_heading = np.array([[np.cos(-heading), -np.sin(-heading), 0],
                       [np.sin(-heading), np.cos(-heading), 0],
                       [0, 0, 1]])
    
    # Rotation matrix for FPA (y-axis)
    R_fpa = np.array([[np.cos(fpa), 0, np.sin(fpa)],
                        [0, 1, 0],
                        [-np.sin(fpa), 0, np.cos(fpa)]])
    # R_fpa = np.array([[1, 0, 0], 
    #                   [0, np.cos(fpa), -np.sin(fpa)], 
    #                   [0, np.sin(fpa), np.cos(fpa)]
    #                 ])
    
    # Rotation matrix for yaw (z-axis)
    #R_yaw = np.array([[np.cos(yaw), -np.sin(yaw), 0],
                       #[np.sin(yaw), np.cos(yaw), 0],
                       #[0, 0, 1]])
    
    # Combined rotation matrix
    #R = np.dot(R_yaw, np.dot(R_pitch, R_roll))
    R = np.dot(R_heading, R_fpa)

    return np.dot(vertices, R.T)


class DescentModule:
    r = 120
    lon = 0
    lat = np.radians(90)

    heading = 0
    fpa = 0
    bank = 0 

    vertices = []

    edges = [(0, 1), (1, 2), (2, 3), (3, 0),
                (4, 5), (5, 6), (6, 7), (7, 4),
                (0, 4), (1, 5), (2, 6), (3, 7)]
    
    def __init__(self):
        x_length = 16
        top_radius = 8
        base_radius = 20

        # Define vertices of a cube
        self.vertices =  np.array([[-x_length/2, -top_radius/2, -top_radius/2],
                            [x_length/2, -base_radius/2, -base_radius/2],
                            [x_length/2, base_radius/2, -base_radius/2],
                            [-x_length/2, top_radius/2, -top_radius/2],
                            [-x_length/2, -top_radius/2, top_radius/2],
                            [x_length/2, -base_radius/2, base_radius/2],
                            [x_length/2, base_radius/2, base_radius/2],
                            [-x_length/2, top_radius/2, top_radius/2]])

    def getVertices(self):
        return self.vertices
    
    def getEdges(self):
        return self.edges
    
    def lines(self, ax):
        return [ax.plot([], [], [])[0] for _ in self.edges]
    
    def getCoM(self):
        return self.r, self.lon, self.lat
    
    def getCoMcart(self):
        x = self.r*cos(self.lat)*cos(self.lon)
        y = self.r*cos(self.lat)*sin(self.lon)
        z = self.r*sin(self.lat)
        return x, y, z
    
    def updatePosition(self, r, lon, lat):
        self.r = r
        self.lon = lon
        self.lat = lat
    
    def updateAttitude(self, heading, fpa, bank):
        self.heading = heading
        self.fpa = fpa
        self.bank = bank

    def plot(self, ax):
        # Rotate vertices
        rot_vertices = rotate(self.getVertices(), self.heading, self.fpa, self.bank)
        
        # Plot edges
        for edge in self.edges:
            x = self.r*cos(self.lat)*cos(self.lon)
            y = self.r*cos(self.lat)*sin(self.lon)
            z = self.r*sin(self.lat)

            start, end = rot_vertices[edge[0]], rot_vertices[edge[1]]
            ax.plot([x + start[0], x + end[0]], [y + start[1], y + end[1]], [z + start[2], z + end[2]], 'b')

    def plotAtOrigin(self, ax):
        # Rotate vertices
        rot_vertices = rotate(self.getVertices(), self.heading, self.fpa, self.bank)
        
        # Plot edges
        for edge in self.edges:
            start, end = rot_vertices[edge[0]], rot_vertices[edge[1]]
            ax.plot([start[0], end[0]], [start[1], end[1]], [start[2], end[2]], 'b')