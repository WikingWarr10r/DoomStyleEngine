import pygame
import sys
from cryptography.fernet import Fernet
import os

pygame.init()

screen_width, screen_height = 800, 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption('Level Editor')

white = (255, 255, 255)
black = (0, 0, 0)
red = (255, 0, 0)
gray = (128, 128, 128)

walls = []
mid_points = []
to_delete = None

def draw_walls():
    for idx, wall in enumerate(walls):
        if type(wall) == tuple:
            pygame.draw.line(screen, black if idx != to_delete else red, wall[:2], wall[2:], 2)

def draw_preview_line(start_pos, end_pos):
    pygame.draw.line(screen, gray, start_pos, end_pos, 2)

def get_key():
    key_path = os.path.join(os.path.dirname(__file__)[:-7], "configs/", "key.key")
    try:
        with open(key_path, 'rb') as key_file:
            key = key_file.read()
            return key
    except FileNotFoundError:
        key = Fernet.generate_key()
        with open(key_path, 'wb') as key_file:
            key_file.write(key)
        return key
    
def encrypt_data(data):
    return cipher_suite.encrypt(data.encode())

def decrypt_data(encrypted_data):
    return cipher_suite.decrypt(encrypted_data).decode()

def write_encrypted_data_to_file():
    with open(os.path.join(os.path.dirname(__file__), "levels/", "main.elvl"), "wb") as f:
        for wall in walls:
            encrypted_data = encrypt_data(','.join([f'{wall[0]},{wall[1]},{wall[2]},{wall[3]}' for wall in walls]))
            f.write(encrypted_data)

def read_encrypted_data_from_file():
    with open(os.path.join(os.path.dirname(__file__), "levels/", "main.elvl"), "rb") as f:
        walls.clear()
        encrypted_data = f.read()
        decrypted_data = decrypt_data(encrypted_data)

        wall_data = decrypted_data.split(',')
        walls_data = [tuple(map(int, wall_data[i:i+4])) for i in range(0, len(wall_data), 4)]
        
        walls.extend(walls_data)

key = get_key()
cipher_suite = Fernet(key)

def generate_mid_points():
    mid_points.clear()
    for wall in walls:
        start_pos = wall[:2]
        end_pos = wall[2:]
        mid_points.append(((start_pos[0] + end_pos[0]) // 2, (start_pos[1] + end_pos[1]) // 2))

def select_wall(pos):
    global to_delete
    for mid_point in mid_points:
        if distance(pos, mid_point) < 100:
            to_delete = mid_points.index(mid_point)
            return

def snap_to_point(pos):
    for wall in walls:
        start_pos = wall[:2]
        end_pos = wall[2:]
        if distance(pos, start_pos) < 10:
            return start_pos
        elif distance(pos, end_pos) < 10:
            return end_pos
    return pos

def distance(p1, p2):
    return ((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2) ** 0.5

running = True
drawing = False
start_pos = None

while running:
    screen.fill(white)
    generate_mid_points()

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1: 
                if not drawing:
                    start_pos = snap_to_point(event.pos)
                    drawing = True
                else:
                    end_pos = snap_to_point(event.pos)
                    walls.append((*start_pos, *end_pos))
                    drawing = False
            elif event.button == 3:  
                select_wall(event.pos)
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_DELETE:
                if to_delete != None:
                    del walls[to_delete]
                    to_delete = None
            if event.key == pygame.K_ESCAPE:
                running = False

            if event.key == pygame.K_s:
                write_encrypted_data_to_file()

            if event.key == pygame.K_l:
                read_encrypted_data_from_file()

    if drawing:
        draw_preview_line(start_pos, snap_to_point(pygame.mouse.get_pos()))

    draw_walls()

    pygame.display.flip()

pygame.quit()
sys.exit()
