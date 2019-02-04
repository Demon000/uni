from entities.ShowEntity import ShowEntity
from entities.ProgramEntity import ProgramEntity
from repositories.ShowRepository import ShowRepository
from services.ShowService import ShowService
from errors.RepositoryError import RepositoryError
from errors.ServiceError import ServiceError

test_lines = [
    'Jurnal,Stiri,1,Informatii\n',
    'Vreme,Stiri,1,Starea vremii\n',
    'Sport,Stiri,1,Noutati in sport\n',
    'Meci,Stiri,2,Romania - Portugalia\n',
    'Viata la sat,Informare,2,Fermieri si chestii\n',
    'Romania te iubesc,Informare,2,Despre tara noastra\n',
    '5 Sense,Film,3,Un film\n',
    'Expandables,Film,3,Alt film\n',
    'Expandables 2,Film,3,Inca un film\n',
    'The mask,Film,3,Ultimul film\n',
]

def test_show_entity():
    show = ShowEntity('Jurnal', 'Stiri', 1, 'Informatii')
    assert show.get_name() == 'Jurnal'
    assert show.get_type() == 'Stiri'
    assert show.get_length() == 1
    assert show.get_description() == 'Informatii'

    show.set_length(2)
    assert show.get_length() == 2

    show.set_description('New description')
    assert show.get_description() == 'New description'

    serialization = show.serialize()
    assert serialization == 'Jurnal,Stiri,2,New description\n'

    deserialized_show = ShowEntity.deserialize(serialization)
    assert show.get_name() == 'Jurnal'
    assert show.get_type() == 'Stiri'
    assert show.get_length() == 2
    assert show.get_description() == 'New description'

    assert show.matches('Jurnal', 'Stiri')
    assert not show.matches('Wrong', 'Stiri')

def test_program_entity():
    show = ShowEntity('Jurnal', 'Stiri', 1, 'Informatii')
    program = ProgramEntity(10, show, True)

def test_show_repository():
    with open('test_shows.txt', 'w') as file:
        file.writelines(test_lines)

    show_repository = ShowRepository('test_shows.txt')
    shows = show_repository.get_shows()
    assert len(shows) == 10

    show = show_repository.find_show('Jurnal', 'Stiri')
    assert show.get_name() == 'Jurnal'
    assert show.get_type() == 'Stiri'

    try:
        show_repository.find_show('Wrong', 'Stiri')
        assert False
    except RepositoryError:
        pass

    show_repository.delete_show(show)
    shows = show_repository.get_shows()
    assert len(shows) == 9

    show = show_repository.find_show('Vreme', 'Stiri')
    assert show.get_length() == 1
    assert show.get_description() == 'Starea vremii'

    show_repository.update_show(show, 2, 'Whatever')
    assert show.get_length() == 2
    assert show.get_description() == 'Whatever'

    show = show_repository.find_show('Vreme', 'Stiri')
    assert show.get_length() == 2
    assert show.get_description() == 'Whatever'

def test_show_service():
    with open('test_shows.txt', 'w') as file:
        file.writelines(test_lines)

    show_repository = ShowRepository('test_shows.txt')
    show_service = ShowService(show_repository)

    shows = show_repository.get_shows()
    assert len(shows) == 10
    show_service.delete_show('Jurnal', 'Stiri')
    shows = show_repository.get_shows()
    assert len(shows) == 9

    with open('test_shows.txt', 'w') as file:
        file.writelines(test_lines)

def test_all():
    test_show_entity()
    test_program_entity()
    test_show_repository()
    test_show_service()

test_all()
print('Tests passed.')
