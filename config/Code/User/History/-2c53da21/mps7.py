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

    # edges = [(0, 1), (1, 2), (2, 3), (3, 0),
    #             (4, 5), (5, 6), (6, 7), (7, 4),
    #             (0, 4), (1, 5), (2, 6), (3, 7)]
    edges = [
        (0, 1), (1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9), (9, 10), (10, 11), (11, 12), (12, 13), (13, 14), (14, 15), (15, 16),
        (17, 18), (18, 19), (19, 20), (20, 21), (21, 22), (22, 23), (23, 24), (24, 25), (25, 26), (26, 27), (27, 28), (28, 29), (29, 30), (30, 31),
        (31, 32), (32, 33),
        (0, 17), (1, 18), (2, 19), (3, 20), (4, 21), (5, 22), (6, 23), (7, 24), (8, 25), (9, 26), (10, 27), (11, 28), (12, 29), (13, 30), (14, 31), (15, 32), (16, 33),
        (0, 8), (1, 7), (2, 6), (3, 5), (9, 15), (10, 14), (11, 13),
        (4, 12),
        (17, 25), (18, 24), (19, 23), (20, 22), (26, 32), (27, 31), (28, 30)
    ]
    
    def __init__(self):
        x_length = 16
        top_radius = 8
        base_radius = 16

        # Define vertices of a cube
        # self.vertices =  np.array([[-x_length/2, -top_radius/2, -top_radius/2],
        #                     [x_length/2, -base_radius/2, -base_radius/2],
        #                     [x_length/2, base_radius/2, -base_radius/2],
        #                     [-x_length/2, top_radius/2, -top_radius/2],
        #                     [-x_length/2, -top_radius/2, top_radius/2],
        #                     [x_length/2, -base_radius/2, base_radius/2],
        #                     [x_length/2, base_radius/2, base_radius/2],
        #                     [-x_length/2, top_radius/2, top_radius/2]])
        self.vertices = [
            [7.3910, 3.0615, 8.0000],
            [5.6569, 5.6569, 8.0000],
            [3.0615, 7.3910, 8.0000],
            [0.0000, 8.0000, 8.0000],
            [-3.0615, 7.3910, 8.0000],
            [-5.6569, 5.6569, 8.0000],
            [-7.3910, 3.0615, 8.0000],
            [-8.0000, 0.0000, 8.0000],
            [-7.3910, -3.0615, 8.0000],
            [-5.6569, -5.6569, 8.0000],
            [-3.0615, -7.3910, 8.0000],
            [-0.0000, -8.0000, 8.0000],
            [3.0615, -7.3910, 8.0000],
            [5.6569, -5.6569, 8.0000],
            [7.3910, -3.0615, 8.0000],
            [8.0000, -0.0000, 8.0000],
            [7.3910, 3.0615, 8.0000],
            [14.7821, 6.1229, -8.0000],
            [11.3137, 11.3137, -8.0000],
            [6.1229, 14.7821, -8.0000],
            [0.0000, 16.0000, -8.0000],
            [-6.1229, 14.7821, -8.0000],
            [-11.3137, 11.3137, -8.0000],
            [-14.7821, 6.1229, -8.0000],
            [-16.0000, 0.0000, -8.0000],
            [-14.7821, -6.1229, -8.0000],
            [-11.3137, -11.3137, -8.0000],
            [-6.1229, -14.7821, -8.0000],
            [-0.0000, -16.0000, -8.0000],
            [6.1229, -14.7821, -8.0000],
            [11.3137, -11.3137, -8.0000],
            [14.7821, -6.1229, -8.0000],
            [16.0000, -0.0000, -8.0000],
            [14.7821, 6.1229, -8.0000]
        ]

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