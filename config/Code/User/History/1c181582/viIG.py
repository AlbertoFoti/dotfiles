from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from PIL import Image

# Define planet properties
mars_radius = 100
mars_texture = "mars.jpg"  # Replace with your Mars texture path

# Lighting variables
light_position = (1.0, 1.0, 1.0, 0.0)
ambient_light = (0.2, 0.2, 0.2, 1.0)
diffuse_light = (0.7, 0.7, 0.7, 1.0)
specular_light = (1.0, 1.0, 1.0, 1.0)

# Camera variables
camera_x = 0.0
camera_y = 0.0
camera_z = 5.0  # Initial camera position
camera_rotation_x = 0.0
camera_rotation_y = 0.0

# Movement speed
movement_speed = 0.1

# Material properties
shininess = 100

def load_texture(filename):
  img = Image.open(filename)
  img_data = img.convert("RGB").tobytes()  # Convert to RGB and get raw data
  width, height = img.size
  texture = glGenTextures(1)
  glBindTexture(GL_TEXTURE_2D, texture)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data)
  return texture

def init():
  # Enable lighting and material
  glEnable(GL_LIGHTING)
  glEnable(GL_LIGHT0)
  glEnable(GL_DEPTH_TEST)
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_light)
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess)
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse_light)

  # Set lighting properties
  glLightfv(GL_LIGHT0, GL_POSITION, light_position)
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light)

  # Load Mars texture
  global mars_texture_id
  mars_texture_id = load_texture(mars_texture)

def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    # Apply camera rotation (optional, replace with desired rotation logic)
    glRotatef(camera_rotation_x, 1.0, 0.0, 0.0)
    glRotatef(camera_rotation_y, 0.0, 1.0, 0.0)

    # Update camera position based on movement
    gluLookAt(camera_x, camera_y, camera_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)

    # Draw Mars with texture
    glEnable(GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, mars_texture_id)
    glutSolidSphere(mars_radius, 20, 20)
    glDisable(GL_TEXTURE_2D)

    glutSwapBuffers()

def reshape(width, height):
  glViewport(0, 0, width, height)
  glMatrixMode(GL_PROJECTION)
  glLoadIdentity()
  gluPerspective(45, float(width)/float(height), 0.1, 100.0)
  glMatrixMode(GL_MODELVIEW)

def handle_key_press(key, x, y):
  global camera_x, camera_y, camera_z, camera_rotation_x, camera_rotation_y

  if key == b'w':  # Move forward
    camera_z -= movement_speed
  elif key == b's':  # Move backward
    camera_z += movement_speed
  elif key == b'a':  # Move left
    camera_x -= movement_speed
  elif key == b'd':  # Move right
    camera_x += movement_speed
  # Add more keys for up/down and rotation if desired
  glutPostRedisplay()  # Trigger redraw on key press

def main():
  glutInit()
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
  glutInitWindowSize(800, 600)
  glutInitWindowPosition(100, 100)
  glutCreateWindow("3D Mars")
  glutDisplayFunc(display)
  glutReshapeFunc(reshape)
  init()
  glutKeyboardFunc(handle_key_press)
  glutMainLoop()

if __name__ == "__main__":
  main()