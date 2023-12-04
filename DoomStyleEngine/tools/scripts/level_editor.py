import pygame
import sys

pygame.init()

screen_width, screen_height = 800, 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption('Level Editor')

white = (255, 255, 255)
black = (0, 0, 0)
red = (255, 0, 0)
gray = (128, 128, 128)

walls = []

def draw_walls():
    for wall in walls:
        pygame.draw.line(screen, black, wall[:2], wall[2:], 2)

def draw_preview_line(start_pos, end_pos):
    pygame.draw.line(screen, gray, start_pos, end_pos, 2)

def delete_wall(pos):
    pass

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
                delete_wall(event.pos)

    if drawing:
        draw_preview_line(start_pos, snap_to_point(pygame.mouse.get_pos()))

    draw_walls()

    pygame.display.flip()

pygame.quit()
sys.exit()