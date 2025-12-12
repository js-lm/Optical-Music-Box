import svgwrite

# in mm
PAGE_WIDTH      = 297.0
PAGE_HEIGHT     = 210.0
CELL_WIDTH      = 5.85
CELL_HEIGHT     = 5.84
BARCODE_HEIGHT  = 12.0
CELL_STROKE_WIDTH = .1

ROWS_COUNT      = 16
COLUMNS_COUNT   = int(PAGE_WIDTH // CELL_WIDTH) 

grid_width = COLUMNS_COUNT * CELL_WIDTH
grid_height = BARCODE_HEIGHT + (ROWS_COUNT * CELL_HEIGHT)

x_offset = (PAGE_WIDTH - grid_width) / 2
y_offset = (PAGE_HEIGHT - grid_height) / 2

drawing = svgwrite.Drawing('grid.svg',
    profile = 'tiny',
    size    = (f'{PAGE_WIDTH}mm', f'{PAGE_HEIGHT}mm')
)
drawing.viewbox(0, 0, PAGE_WIDTH, PAGE_HEIGHT)

grid_group = drawing.add(drawing.g(transform=f'translate({x_offset},{y_offset})'))

# bar code
for column in range(COLUMNS_COUNT):
    x = column * CELL_WIDTH
    y = 0
    
    # even -> blank, odd -> black
    fill_color = 'black' if column % 2 != 0 else 'none'
    
    grid_group.add(drawing.rect(
        insert      = (x, y),
        size        = (CELL_WIDTH, BARCODE_HEIGHT),
        fill        = fill_color,
        stroke      = 'black',
        stroke_width= 0
    ))

for row in range(ROWS_COUNT):
    for column in range(COLUMNS_COUNT):
        x = column * CELL_WIDTH
        y = BARCODE_HEIGHT + (row * CELL_HEIGHT)
        
        grid_group.add(drawing.rect(
            insert      = (x, y),
            size        = (CELL_WIDTH, CELL_HEIGHT),
            fill        = 'none',
            stroke      = 'black',
            stroke_width= CELL_STROKE_WIDTH
        ))

drawing.save()