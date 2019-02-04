from errors.RepositoryError import RepositoryError
from errors.ServiceError import ServiceError

class Console():
    def __init__(self, show_service):
        self.__show_service = show_service

    def __delete_show(self):
        name = input('Show name: ')
        type_ = input('Show type: ')

        show = self.__show_service.delete_show(name, type_)
        print('Deleted show: ', show)

    def __update_show(self):
        name = input('Show name: ')
        type_ = input('Show type: ')

        while True:
            raw_length = input('New show length: ')
            try:
                length = int(raw_length)
                break
            except ValueError:
                print('The given length is not a number.')

        description = input('New show description: ')

        show = self.__show_service.update_show(name, type_, length, description)
        print('Updated show: ', show)

    def __generate_programs(self):
        programs = self.__show_service.generate_programs(10, 22)
        print('Hour\tName\tType\tDescription(*)')
        for program in programs:
            print(program)

    def __block_type(self):
        type_ = input('Type to block: ')
        self.__show_service.block_type(type_)

    def __unblock_type(self):
        type_ = input('Type to unblock: ')
        self.__show_service.unblock_type(type_)

    def __clear_blocked_types(self):
        self.__show_service.clear_blocked_types()

    def __get_menu(self):
        menu = {
            '1': ['Delete show', self.__delete_show],
            '2': ['Update show', self.__update_show],
            '3': ['Generate programs', self.__generate_programs],
            '4': ['Block type', self.__block_type],
            '5': ['Unblock type', self.__unblock_type],
            '6': ['Clear blocked types', self.__clear_blocked_types],
        }

        return menu

    def __print_menu(self):
        menu = self.__get_menu()
        for key, entry in menu.items():
            print('{}. {}'.format(key, entry[0]))

    def __run_option(self):
        menu = self.__get_menu()
        option = input('Select an option: ')
        if option not in menu:
            print('Option is invalid.')
            return

        entry = menu[option]
        entry[1]()


    def run(self):
        while True:
            self.__print_menu()
            try:
                self.__run_option()
            except (RepositoryError, ServiceError) as err:
                print(err)
