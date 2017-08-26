'''
Relationship between gravitational force
& distance between two bodies
'''
import matplotlib.pyplot as plt

#Draw the Graph
def draw_graph(x, y):
    plt.plot(x, y, marker='o')
    plt.xlabel('Distance in meters')
    plt.ylabel('Gravitational force in newtons')
    plt.title('Gravitation force and distance')
    plt.show()

def generate_F_r():
    # Generate values for r
    r = range(100, 1001, 50)
    # Empty list to store calc values
    F = []
    
    # Constant G
    G = 6.674*(10**-11)
    # 2 masses
    m1 = 0.5
    m2 = 1.5
    
    # Calculate force & add to list
    for dist in r:
        force = G*(m1*m2)/(dist**2)
        F.append(force)
    
    # Call the draw_graph function
    draw_graph(r, F)
    
if __name__ == '__main__':
    generate_F_r()
