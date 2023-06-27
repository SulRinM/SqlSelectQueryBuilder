#include <iostream>
#include <vector>
#include <sstream>

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder() {
        query = "SELECT * ";
        fromAdded = false;
        whereAdded = false;
    }

    SqlSelectQueryBuilder& AddColumn(const std::string& column) {
        if (query.find("*") != std::string::npos) {
            query.replace(query.find("*"), 1, "");
            query += column;
        }
        else {
            query += ", " + column;
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& tableName) {
        if (!fromAdded) {
            query += " FROM " + tableName;
            fromAdded = true;
        }
        else {
            query.replace(query.find("FROM ") + 5, query.length(), tableName);
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) {
        if (!whereAdded) {
            query += " WHERE " + column + "=" + value;
            whereAdded = true;
        }
        else {
            query += " AND " + column + "=" + value;
        }
        return *this;
    }

    std::string BuildQuery() {
        if (!fromAdded) {
            query += " FROM ";
        }
        query += ";";
        return query;
    }

private:
    std::string query;
    bool fromAdded;
    bool whereAdded;
};

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::cout << query_builder.BuildQuery() << std::endl;

    return 0;
}