import matplotlib.pyplot as plt
import numpy as np

def plot_data(filename):
  # Read data from file
  data = np.loadtxt(filename, delimiter=',')  # Assumes comma-separated data

  # Extract x and y values
  x = data[:, 0]  # First column
  y = data[:, 1]  # Second column

  # Create the plot
  plt.plot(x, y)
  plt.xlabel("X-axis")
  plt.ylabel("Y-axis")
  plt.title("Data Plot")
  plt.grid(True)
  plt.show()

if __name__ == "__main__":
  filename = "mu_nominal_profile.txt"  # Replace with your actual filename
  plot_data(filename)