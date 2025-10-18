import tkinter as tk
import serial
import time
import math
import requests
'''
try:
    arduino = serial.Serial('COM20', 9600, timeout=1)
    time.sleep(2)  # Wait for connection to establish
    print("Connected to ESP8266")
except:
    print("Failed to connect to ESP8266")
    exit()
'''
def update_trunk(angle):
    '''
    angle=str(angle) + "\n"
    arduino.write(angle.encode())
    arduino.flush()
'''
    angle = math.radians(int(angle))
    x = 150 - 100 * math.cos(math.pi/2+angle)
    y = 150 + 100 * math.sin(math.pi/2+angle)
    canvas.coords(trunk, 150, 150, x, y)


root = tk.Tk()
root.title("Elephant Trunk")

canvas = tk.Canvas(root, width=300, height=300, bg="white")
canvas.pack()

trunk = canvas.create_line(150, 150, 150, 250, width=8, fill="gray")


slider = tk.Scale(root, from_=0, to=180, orient="horizontal", length=200, command=update_trunk)
slider.pack()

root.mainloop()

'''
import tkinter as tk
import serial
import time

# Connect to ESP8266 (change COM20 to your actual port)
try:
    arduino = serial.Serial('COM20', 9600, timeout=1)
    time.sleep(2)  # Wait for connection to establish
    print("Connected to ESP8266")
except:
    print("Failed to connect to ESP8266")
    exit()


def update_brightness(value):
    try:
        # Send the value with newline character
        message = str(value) + "\n"
        arduino.write(message.encode())
        arduino.flush()  # Ensure data is sent immediately

        # Optional: Read confirmation
        # response = arduino.readline().decode().strip()
        # print(f"Brightness set to: {value}")

    except Exception as e:
        print(f"Error sending data: {e}")


def on_closing():
    """Clean up when closing the window"""
    try:
        arduino.close()
    except:
        pass
    root.destroy()


# Create the GUI
root = tk.Tk()
root.title("LED Brightness Control")
root.geometry("400x150")

# Add a label
label = tk.Label(root, text="LED Brightness Control", font=("Arial", 12))
label.pack(pady=10)

# Create the slider
slider = tk.Scale(root, from_=0, to=255, orient="horizontal",
                  command=update_brightness, length=300,
                  resolution=1, label="Brightness Level")
slider.pack(pady=20)

# Set initial value
slider.set(0)

# Handle window closing
root.protocol("WM_DELETE_WINDOW", on_closing)

# Run the GUI
root.mainloop()
'''