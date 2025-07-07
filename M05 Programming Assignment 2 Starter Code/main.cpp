#include "sqlite3.h"
#include <iostream>
#include <iomanip>
#include <string>

void printMainMenu();
void viewRental(sqlite3 *);
void viewCustomer(sqlite3 *);
int mainMenu();
void printCustomerPage(sqlite3_stmt *, int, int);
void printRentalPage(sqlite3_stmt *, int, int);
	
int main()
{
	int choice;

	sqlite3 *mydb;

	int rc; 

	rc = sqlite3_open("sakila.db", &mydb);

	if (rc)
	{
		std::cout << "Error opening database: " << sqlite3_errmsg(mydb) << std::endl;
		return 1;
	}
	
	std::cout << "Welcome to Sakila" << std::endl;
	choice = mainMenu();
	while (true)
	{
		switch (choice) 
		{
			case 1: viewRental(mydb); break;
			case 2: viewCustomer(mydb); break;
			case -1: 
				sqlite3_close(mydb);
				return 0;
			default: std::cout << "That is not a valid choice." << std::endl;
		}
		std::cout << "\n\n";
		choice = mainMenu();
	}
	
} 

void printMainMenu()
{
	std::cout << "Please choose an option (enter -1 to quit):  " << std::endl;
	std::cout << "1. View the rentals for a customer" << std::endl;
	std::cout << "2. View Customer Information" << std::endl;
	std::cout << "Enter Choice: ";
}

int mainMenu()
{
	int choice = 0;

	printMainMenu();
	std::cin >> choice;
	while ((!std::cin || choice < 1 || choice > 2) && choice != -1)
	{
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		std::cout << "That is not a valid choice." << std::endl
			 << std::endl;
		printMainMenu();
		std::cin >> choice;
	}
	return choice;
}

void viewRental(sqlite3 *db)
{
	std::string query = "SELECT customer_id, first_name, last_name FROM customer ";
	sqlite3_stmt *pRes;
	std::string m_strLastError;
	std::string query2;
	std::string cusID;
	std::string cus_fname, cus_lname;
	if (sqlite3_prepare_v2(db, query.c_str(), -1, &pRes, NULL) != SQLITE_OK)
	{
		m_strLastError = sqlite3_errmsg(db);
		sqlite3_finalize(pRes);
		std::cout << "There was an error: " << m_strLastError << std::endl;
		return;
	}
	else
	{
		int columnCount = sqlite3_column_count(pRes);
		int i = 0, choice = 0, rowsPerPage, totalRows;
		sqlite3_stmt *pRes2;
		std::cout << std::left;
		int res;
		do
		{
			res = sqlite3_step(pRes);
			i++;

		} while (res == SQLITE_ROW);
		totalRows = i - 1;
		sqlite3_reset(pRes);
		std::cout << "There are " << i - 1 << " rows in the result.  How many do you want to see per page?" << std::endl;
		std::cin >> rowsPerPage;
		while (!std::cin || rowsPerPage < 0)
		{
			if (!std::cin)
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
			std::cout << "That is not a valid choice! Try again!" << std::endl;
			std::cout << "There are " << i << " rows in the result.  How many do you want to see per page?" << std::endl;
		}
		if (rowsPerPage > i)
			rowsPerPage = i;
		i = 0;

		while (choice == 0 || choice == -1)
		{
			if (i == 0)
				std::cout << "Please choose the customer you want to see rentals for (enter 0 to go to the next page):" << std::endl;
			else if (i + rowsPerPage < totalRows)
				std::cout << "Please choose the customer you want to see rentals for (enter 0 to go to the next page or -1 to go to the previous page):" << std::endl;
			else
				std::cout << "Please choose the customer you want to see rentals for (enter -1 to go to the previous page):" << std::endl;
			printCustomerPage(pRes, rowsPerPage, i);
			std::cin >> choice;
		
			while (!(std::cin) || choice < -1 || choice > totalRows)
			{
				if (!std::cin)
				{
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}
				std::cout << "That is not a valid choice! Try again!" << std::endl;
				std::cin >> choice;
			}
			if (choice == 0)
			{
				i = i + rowsPerPage;

				if (i >= totalRows)
				{
					i = totalRows - rowsPerPage;
					sqlite3_reset(pRes);
					for (int j = 0; j < i; j++)
					{
						sqlite3_step(pRes);
					}
				}
			}
			else if (choice == -1)
			{
				i = i - rowsPerPage;
				if (i < 0)
					i = 0;
				sqlite3_reset(pRes);
				for (int j = 0; j < i; j++)
					sqlite3_step(pRes);
			}
		}
		sqlite3_reset(pRes);
		for (int i = 0; i < choice; i++)
			sqlite3_step(pRes);
		cusID = reinterpret_cast<const char *>(sqlite3_column_text(pRes, 0));
		cus_fname = reinterpret_cast<const char *>(sqlite3_column_text(pRes, 1));
		cus_lname = reinterpret_cast<const char *>(sqlite3_column_text(pRes, 2));
		sqlite3_finalize(pRes);
		query2 = "select rental_id, rental_date, return_date, staff.first_name || ' ' || staff.last_name as 'Staff Name', ";
		query2 += "film.title, film.description, film.rental_rate ";
		query2 += "from rental join staff on rental.staff_id = staff.staff_id ";
		query2 += "join inventory on rental.inventory_id = inventory.inventory_id ";
		query2 += "join film on film.film_id = inventory.film_id ";
		query2 += "where customer_id = " + cusID;

		if (sqlite3_prepare_v2(db, query2.c_str(), -1, &pRes2, NULL) != SQLITE_OK)
		{
			m_strLastError = sqlite3_errmsg(db);
			sqlite3_finalize(pRes2);
			std::cout << "There was an error: " << m_strLastError << std::endl;
			return;
		}
		else
		{
			columnCount = sqlite3_column_count(pRes);
			i = 0;
			choice = 0;

			do
			{
				res = sqlite3_step(pRes2);
				i++;

			} while (res == SQLITE_ROW);
			totalRows = i;
			sqlite3_reset(pRes2);
			std::cout << "There are " << i << " rows in the result.  How many do you want to see per page?" << std::endl;
			std::cin >> rowsPerPage;
			while (!std::cin || rowsPerPage < 0)
			{
				if (!std::cin)
				{
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
				}
				std::cout << "That is not a valid choice! Try again!" << std::endl;
				std::cout << "There are " << i << " rows in the result.  How many do you want to see per page?" << std::endl;
			}
			if (rowsPerPage > i)
				rowsPerPage = i;
			i = 0;

			while (choice == 0 || choice == -1)
			{
				if (i == 0)
					std::cout << "Please choose the rental you want to see (enter 0 to go to the next page):" << std::endl;
				else if (i + rowsPerPage < totalRows)
					std::cout << "Please choose the rental you want to see (enter 0 to go to the next page or -1 to go to the previous page):" << std::endl;
				else
					std::cout << "Please choose the rental you want to see (enter -1 to go to the previous page):" << std::endl;
				printRentalPage(pRes2, rowsPerPage, i);
				std::cin >> choice;
			
				while (!(std::cin) || choice < -1 || choice > totalRows)
				{
					if (!std::cin)
					{
						std::cin.clear();
						std::cin.ignore(INT_MAX, '\n');
					}
					std::cout << "That is not a valid choice! Try again!" << std::endl;
					std::cin >> choice;
				}
				if (choice == 0)
				{
					i = i + rowsPerPage;
					if (i >= totalRows)
					{
						i = totalRows - rowsPerPage;
						sqlite3_reset(pRes2);
						for (int j = 0; j < i; j++)
							sqlite3_step(pRes2);
					}
				}
				else if (choice == -1)
				{
					i = i - rowsPerPage;
					if (i < 0)
						i = 0;
					sqlite3_reset(pRes2); 
					for (int j = 0; j < i; j++)
						sqlite3_step(pRes2);
				}
			}
			sqlite3_reset(pRes2);
			for (int i = 0; i < choice; i++)
				sqlite3_step(pRes2);
		}
		std::string rentalID = reinterpret_cast<const char *>(sqlite3_column_text(pRes2, 0));
		std::string rentalDate = reinterpret_cast<const char *>(sqlite3_column_text(pRes2, 1));
		std::string returnDate;
		if(sqlite3_column_type(pRes2,2) != SQLITE_NULL)
			returnDate = reinterpret_cast<const char *>(sqlite3_column_text(pRes2, 2));
		else 
			returnDate = "";
		std::string staff = reinterpret_cast<const char *>(sqlite3_column_text(pRes2, 3));
		std::string filmTitle = reinterpret_cast<const char *>(sqlite3_column_text(pRes2, 4));
		std::string filmdescription = reinterpret_cast<const char *>(sqlite3_column_text(pRes2, 5));
		std::string rentalRate = reinterpret_cast<const char *>(sqlite3_column_text(pRes2, 6));
		std::cout << std::showpoint << std::fixed << std::setprecision(2);
		std::cout << "Rental Date: " << rentalDate << std::endl;
		std::cout << "Staff: " << staff << std::endl;
		std::cout << "Customer: " << cus_fname << " " << cus_lname << std::endl;
		std::cout << "Film Information:" << std::endl;
		std::cout << filmTitle << " - " << filmdescription << " $" << rentalRate << std::endl;
		std::cout << "Return Date: " << returnDate << std::endl;
		sqlite3_finalize(pRes2);
	}
}

void printCustomerPage(sqlite3_stmt *res, int rowsPerPage, int startNum)
{
	int stop, i = 1;
	do
	{
		stop = sqlite3_step(res);
		if (stop != SQLITE_ROW)
			break;
		std::cout << i + startNum << ". ";
		if (sqlite3_column_type(res, 0) != SQLITE_NULL)
			std::cout << sqlite3_column_text(res, 0) << " - ";
		if (sqlite3_column_type(res, 1) != SQLITE_NULL)
			std::cout << sqlite3_column_text(res, 1) << " ";
		if (sqlite3_column_type(res, 2) != SQLITE_NULL)
			std::cout << sqlite3_column_text(res, 2) << " ";
		std::cout << std::endl;
		i++;

	} while (i <= rowsPerPage);
}

void printRentalPage(sqlite3_stmt *res, int rowsPerPage, int startNum)
{
	int stop, i = 1;
	do
	{
		stop = sqlite3_step(res);
		if (stop != SQLITE_ROW)
			break;
		std::cout << i + startNum << ". ";
		if (sqlite3_column_type(res, 0) != SQLITE_NULL)
			std::cout << sqlite3_column_text(res, 0) << " - ";
		if (sqlite3_column_type(res, 1) != SQLITE_NULL)
			std::cout << sqlite3_column_text(res, 1) << " ";
		std::cout << std::endl;
		i++;

	} while (i <= rowsPerPage);
}

void viewCustomer(sqlite3 *db)
{
	std::string query = "SELECT customer_id, last_name, first_name FROM customer ORDER BY customer_id";
    sqlite3_stmt *pRes;
    std::string m_strLastError;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &pRes, NULL) != SQLITE_OK)
    {
        m_strLastError = sqlite3_errmsg(db);
        sqlite3_finalize(pRes);
        std::cout << "There was an error: " << m_strLastError << std::endl;
        return;
    }

    int totalRows = 0;
    while (sqlite3_step(pRes) == SQLITE_ROW)
    {
        totalRows++;
    }
    sqlite3_reset(pRes);

    int rowsPerPage;
    std::cout << "There are " << totalRows << " rows in the result. How many do you want to see per page?" << std::endl;
    std::cin >> rowsPerPage;
    while (!std::cin || rowsPerPage <= 0)
    {
        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
        std::cout << "That is not a valid choice! Try again!" << std::endl;
        std::cout << "There are " << totalRows << " rows in the result. How many do you want to see per page?" << std::endl;
        std::cin >> rowsPerPage;
    }

    int choice = 0;
    int page = 0;
    while (true)
    {
        int startRow = page * rowsPerPage;
        if (startRow >= totalRows) {
            startRow = (totalRows / rowsPerPage) * rowsPerPage;
            if (totalRows % rowsPerPage == 0 && totalRows > 0) {
                startRow -= rowsPerPage;
            }
             if (startRow < 0) startRow = 0;
        }

        sqlite3_reset(pRes);
        for(int k = 0; k < startRow; ++k) sqlite3_step(pRes);


        std::cout << "Please choose the customer you want to see:" << std::endl;
        for (int i = 0; i < rowsPerPage && sqlite3_step(pRes) == SQLITE_ROW; ++i)
        {
            std::cout << sqlite3_column_text(pRes, 0) << ". " << sqlite3_column_text(pRes, 1) << " " << sqlite3_column_text(pRes, 2) << std::endl;
        }

        if(startRow == 0)
             std::cout << "Enter 0 to go to the next page" << std::endl;
        else if (startRow + rowsPerPage >= totalRows)
            std::cout << "Enter -1 to go to the previous page" << std::endl;
        else
            std::cout << "Enter 0 to go to the next page or -1 to go to the previous page" << std::endl;

        std::cin >> choice;
        while (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << "That is not a valid choice! Try again!" << std::endl;
            std::cin >> choice;
        }

        if (choice == 0)
        {
            if (startRow + rowsPerPage < totalRows)
                page++;
        }
        else if (choice == -1)
        {
            if (page > 0)
                page--;
        }
        else if (choice > 0 && choice <= totalRows)
        {
            break;
        } else {
            std::cout << "That is not a valid choice! Try again!" << std::endl;
        }
    }
    sqlite3_finalize(pRes);

    std::string query2 = "SELECT c.first_name, c.last_name, a.phone, a.address, ci.city, c.email, c.active, c.last_update "
                         "FROM customer c "
                         "JOIN address a ON c.address_id = a.address_id "
                         "JOIN city ci ON a.city_id = ci.city_id "
                         "WHERE c.customer_id = ?";
    
    sqlite3_stmt *pRes2;
    if (sqlite3_prepare_v2(db, query2.c_str(), -1, &pRes2, NULL) != SQLITE_OK)
    {
        m_strLastError = sqlite3_errmsg(db);
        sqlite3_finalize(pRes2);
        std::cout << "There was an error: " << m_strLastError << std::endl;
        return;
    }

    sqlite3_bind_int(pRes2, 1, choice);

    if (sqlite3_step(pRes2) == SQLITE_ROW)
    {
        std::cout << "----Customer Information----" << std::endl;
        std::cout << "Name: " << sqlite3_column_text(pRes2, 0) << " " << sqlite3_column_text(pRes2, 1) << std::endl;
        std::cout << "Address: " << sqlite3_column_text(pRes2, 3) << std::endl;
		std::cout << sqlite3_column_text(pRes2, 4) << std::endl;
        std::cout << "Phone Number: " << sqlite3_column_text(pRes2, 2) << std::endl;
        std::cout << "Email: " << sqlite3_column_text(pRes2, 5) << std::endl;
        std::cout << "Active: " << (sqlite3_column_int(pRes2, 6) ? "Yes" : "No") << std::endl;
        std::cout << "Last Update: " << sqlite3_column_text(pRes2, 7) << std::endl;
    }

    sqlite3_finalize(pRes2);
}


	