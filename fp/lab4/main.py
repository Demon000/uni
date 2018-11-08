from ui import ui_run
from cli import cli_run

print('Press 1 to use a menu-based interface or 2 to use a command-based one.')

while True:
    choice = input('Interface type: ')

    try:
        menu_type = int(choice)
    except ValueError:
        print('Invalid option.')

    if menu_type == 1:
        ui_run()
    elif menu_type == 2:
        cli_run()
    else:
        print('Invalid option.')

