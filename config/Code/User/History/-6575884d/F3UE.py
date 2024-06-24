import matplotlib.pyplot as plt
import numpy as np

def plot_data(filename):
  # Read data from file
  data = np.genfromtxt(filename, delimiter="\n")

  # Extract x and y values
  y = data  # First column
  x = np.arange(1, len(y) + 1)

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