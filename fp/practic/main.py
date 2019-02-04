from repositories.ShowRepository import ShowRepository

from services.ShowService import ShowService

from UI.Console import Console

def main():
    show_repository = ShowRepository('shows.txt')
    show_service = ShowService(show_repository)

    console = Console(show_service)
    console.run()

main()
print('Goodbye.')
