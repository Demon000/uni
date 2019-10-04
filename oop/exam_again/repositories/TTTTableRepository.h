#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "../entities/TTTTable.h"

#ifndef TTT_TABLE_REPOSITORY_H
#define TTT_TABLE_REPOSITORY_H

class TableExistsException : std::exception {};
class TableMissingException : std::exception {};

class TTTTableRepository {
public:
	TTTTableRepository(std::string path) : path{path} {}

	/*
	 * Get the tables present in the file.
	 *
	 * @return the tables present in the file.
	 */
	std::vector<TTTTable> getTables() const {
		return readTables();
	}

	/*
	 * Get a table by id if present in the file.
	 *
	 * @return the table if present in the file.
	 */
	TTTTable getTableById(int id) const {
		std::vector<TTTTable> ttttables = readTables();
		for (TTTTable t : ttttables) {
			if (t.getId() == id) {
				return t;
			}
		}

		throw TableMissingException();
	}

	/*
	 * Add a table to the file.
	 *
	 * @param ttttable the table to be added.
	 */
	void addTable(TTTTable ttttable) const {
		std::vector<TTTTable> ttttables = readTables();
		for (const TTTTable& t : ttttables) {
			if (t.getId() == ttttable.getId()) {
				throw TableExistsException();
			}
		}

		ttttables.push_back(ttttable);
		writeTables(ttttables);
	}

	/*
	 * Update a table data in the file.
	 *
	 * @param ttttable the table to be updated.
	 */
	void updateTable(TTTTable ttttable) const {
		std::vector<TTTTable> ttttables = readTables();
		for (auto ti = ttttables.begin(); ti < ttttables.end(); ti++) {
			if ((*ti).getId() == ttttable.getId()) {
				*ti = ttttable;
				writeTables(ttttables);
				return;
			}
		}

		throw TableMissingException();
	}

private:
	/*
	 * Read the tables present in the file.
	 *
	 * @return the tables present in the file.
	 */
	std::vector<TTTTable> readTables() const {
		std::vector<TTTTable> ttttables;
		std::ifstream in(path);

		std::string line;
		std::string word;
		std::vector<std::string> words;
		while(getline(in, line)) {
			std::stringstream ss(line);
			words.clear();

			while(getline(ss, word, ',')) {
				words.push_back(word);
			}

			int id = stoi(words[0]);
			int size = stoi(words[1]);
			std::string table = words[2];
			std::string nextPlayer = words[3];
			std::string state = words[4];

			TTTTable ttttable{id, size, table, nextPlayer, state};
			ttttables.push_back(ttttable);
		}

		return ttttables;
	}

	/*
	 * Write the given tables to the file.
	 *
	 * @param ttttables the tables to be written to the file.
	 */
	void writeTables(const std::vector<TTTTable>& ttttables) const {
		std::ofstream out(path);
		for (const TTTTable& ttttable : ttttables) {
			out << ttttable.getId() << ","
				<< ttttable.getSize() << ","
				<< ttttable.getTable() << ","
				<< ttttable.getNextPlayer() << ","
				<< ttttable.getState() << "\n";
		}
	}

	std::string path;
};

#endif // TTT_TABLE_REPOSITORY_H
