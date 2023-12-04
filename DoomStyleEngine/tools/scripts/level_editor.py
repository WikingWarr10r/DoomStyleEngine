import pygame
import sys

pygame.init()

screen_width, screen_height = 800, 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption('Level Editor')

white = (255, 255, 255)
black = (0, 0, 0)
red = (255, 0, 0)

walls = []

def draw_walls():
    for wall in walls:
        pygame.draw.line(screen, black, wall[:2], wall[2:], 2)

def delete_wall(pos):
    pass

running = True
drawing = False

while running:
    screen.fill(white)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1: 
                if not drawing:
                    start_pos = event.pos
                    drawing = True
                else:
                    end_pos = event.pos
                    walls.append((*start_pos, *end_pos))
                    drawing = False
            elif event.button == 3:  
                delete_wall(event.pos)

    draw_walls()

    pygame.display.flip()

pygame.quit()
sys.exit()