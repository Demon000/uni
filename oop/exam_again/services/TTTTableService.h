#include <vector>
#include <string>
#include <algorithm>

#include "../entities/TTTTable.h"
#include "../validators/TTTTableValidator.h"
#include "../repositories/TTTTableRepository.h"
#include "../observe/Observe.h"

#ifndef TTT_TABLE_SERVICE_H
#define TTT_TABLE_SERVICE_H

class TTTTableService : public Observable {
public:
	TTTTableService(TTTTableRepository& repository, TTTTableValidator& validator)
			: repository{repository}, validator{validator} {}

	/*
	 * Get the tables present in the repository, sorted by state.
	 *
	 * @return the tables present in the repository.
	 */
	std::vector<TTTTable> getTables() {
		std::vector<TTTTable> ttttables = repository.getTables();
		std::sort(ttttables.begin(), ttttables.end(),
				[](const TTTTable& first, const TTTTable& second) {
			return first.getState() < second.getState();
		});

		return ttttables;
	}

	/*
	 * Get a table by id if present in the repository.
	 *
	 * @param id the id to look for.
	 *
	 * @return the table found.
	 */
	TTTTable getTableById(int id) {
		return repository.getTableById(id);
	}

	/*
	 * Add a table to the repository.
	 *
	 * @param id the id of the table.
	 * @param size the size of the table.
	 * @param table the table of the table.
	 * @param nextPlayer the next player of the table.
	 */
	void addTable(int id, int size, std::string table,
			std::string nextPlayer) {
		TTTTable ttttable = TTTTable{id, size, table, nextPlayer};

		validator.validateSize(size);
		validator.validateTable(size, table);
		validator.validateNextPlayer(nextPlayer);

		repository.addTable(ttttable);
		notify(ObserveEvent::CHANGE);
	}

	/*
	 * Update a table if present in the repository.
	 *
	 * @param id the id to look for.
	 * @param size the new size of the table.
	 * @param table the new table of the table.
	 * @param nextPlayer the new next player of the table.
	 * @param state the new state of the table.
	 */
	void updateTable(int id, int size, std::string table,
			std::string nextPlayer, std::string state) {
		TTTTable ttttable = repository.getTableById(id);

		validator.validateSize(size);
		validator.validateTable(size, table);
		validator.validateNextPlayer(nextPlayer);
		validator.validateState(state);

		ttttable.setSize(size);
		ttttable.setTable(table);
		ttttable.setNextPlayer(nextPlayer);
		ttttable.setState(state);

		repository.updateTable(ttttable);
		notify(ObserveEvent::CHANGE);
	}

	/*
	 * Play this turn of the table by filling a cell.
	 *
	 * @param id the id to look for.
	 * @param x the x value of the table cell.
	 * @param y the y value of the table cell.
	 */
	void playTable(int id, int x, int y) {
		TTTTable ttttable = repository.getTableById(id);

		int size = ttttable.getSize();
		validator.validatePosition(size, x, y);

		ttttable.playTable(x, y);

		repository.updateTable(ttttable);
		notify(ObserveEvent::CHANGE);
	}

private:
	TTTTableRepository& repository;
	TTTTableValidator& validator;
};

#endif // TTT_TABLE_SERVICE_H
