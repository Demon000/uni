#include <cassert>
#include <iostream>

#include "entities/TTTTable.h"
#include "repositories/TTTTableRepository.h"
#include "validators/TTTTableValidator.h"
#include "services/TTTTableService.h"

void test_table_service() {
    TTTTableRepository repository{"test_table_service.csv"};
    TTTTableValidator validator;
    TTTTableService service{repository, validator};
    std::vector<TTTTable> ttttables;
    TTTTable ttttable;

    service.addTable(1, 3, "---------", "X");
    ttttable = service.getTableById(1);
    assert(ttttable.getId() == 1);
    assert(ttttable.getSize() == 3);
    assert(ttttable.getTable() == "---------");
    assert(ttttable.getNextPlayer() == "X");
    assert(ttttable.getState() == "Not started");

    service.updateTable(1, 4, "----------------", "0", "In progress");
    ttttable = service.getTableById(1);
    assert(ttttable.getId() == 1);
    assert(ttttable.getSize() == 4);
    assert(ttttable.getTable() == "----------------");
    assert(ttttable.getNextPlayer() == "0");
    assert(ttttable.getState() == "In progress");

    service.playTable(1, 3, 3);
    ttttable = service.getTableById(1);
    assert(ttttable.getNextPlayer() == "X");
    assert(ttttable.getTable()[15] == '0');

    service.addTable(2, 4, "X-0-------------", "0");
    ttttables = service.getTables();
    assert(ttttables.size() == 2);

    service.addTable(3, 5, "X-0-X-0------------------", "X");

    try {
        service.addTable(1, 3, "---------", "X");
        assert(false);
    } catch(TableExistsException&) {
        assert(true);
    }

    try {
        service.getTableById(4);
        assert(false);
    } catch(TableMissingException&) {
        assert(true);
    }

    try {
        service.updateTable(4, 3, "---------", "X", "Finished");
        assert(false);
    } catch(TableMissingException&) {
        assert(true);
    }

    try {
        service.addTable(1, 6, "---------", "X");
        assert(false);
    } catch(InvalidTableSizeException&) {
        assert(true);
    }

    try {
        service.addTable(1, 3, "-----bla-", "X");
        assert(false);
    } catch(InvalidTableException&) {
        assert(true);
    }

    try {
        service.addTable(1, 4, "---------", "X");
        assert(false);
    } catch(InvalidTableException&) {
        assert(true);
    }

    try {
        service.addTable(1, 3, "---------", "H");
        assert(false);
    } catch(InvalidNextPlayerException&) {
        assert(true);
    }

    try {
        service.updateTable(1, 3, "---------", "X", "Invalid state");
        assert(false);
    } catch(InvalidTableStateException&) {
        assert(true);
    }
}

int main() {
    test_table_service();

    return 0;
}
