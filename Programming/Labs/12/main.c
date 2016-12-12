#include "AddToFile.h"
#include "RemoveFromFile.h"
#include "ModifyTableContent.h"
#include "PrintTable.h"
#include "TaskFunctions.h"

int main(const int argc, const char* argv[]) {
	xmlInitParser();
	xmlKeepBlanksDefault(0);

	while (true) {

		fprintf(stdout, BOLD(RED("Add to table { 1 }\n")));
		fprintf(stdout, BOLD(GREEN("Remove from table { 2 }\n")));
		fprintf(stdout, BOLD(YELLOW("Modify table content { 3 }\n")));
		fprintf(stdout, BOLD(BLUE("Print table { 4 }\n")));
		fprintf(stdout, BOLD(MAGENTA("Request for database { 5 }\n\n")));

		int action_choice = 0;
		int id = 0;

		fprintf(stdout, BOLD(CYAN("Enter your choice: ")));

		if (fscanf(stdin, "%d", &action_choice) != 1) {
			goto END;
		}

		fgetc(stdin);
		fprintf(stdout, BOLD("----------------------------------------------\n"));

		switch (action_choice) {

			case 1:

				fprintf(stdout, "Examples/XML_Suppliers.xml { 1 }\n");
				fprintf(stdout, "Examples/XML_Products.xml { 2 }\n");
				fprintf(stdout, "Examples/XML_Shipments.xml { 3 }\n\n");

				fprintf(stdout, "Choose table to add to: ");

				if (fscanf(stdin, "%d", &action_choice) != 1) {
					goto END;
				}

				fgetc(stdin);
				fprintf(stdout, BOLD("----------------------------------------------\n"));

				switch (action_choice) {

					case 1:
						AddToFile("Examples/XML_Suppliers.xml", AddSupplier);
						break;

					case 2:
						AddToFile("Examples/XML_Products.xml", AddProduct);
						break;

					case 3:
						AddToFile("Examples/XML_Shipments.xml", AddShipment);
						break;

					default:
						goto END;
				}

				break;

			case 2:

				fprintf(stdout, "Examples/XML_Suppliers.xml { 1 }\n");
				fprintf(stdout, "Examples/XML_Products.xml { 2 }\n");
				fprintf(stdout, "Examples/XML_Shipments.xml { 3 }\n\n");

				fprintf(stdout, "Choose table to remove from: ");

				if (fscanf(stdin, "%d", &action_choice) != 1) {
					goto END;
				}

				fgetc(stdin);
				fprintf(stdout, "Enter ID to remove: ");

				if (fscanf(stdin, "%d", &id) != 1) {
					goto END;
				}

				fprintf(stdout, BOLD("----------------------------------------------\n"));

				switch (action_choice) {

					case 1:
						RemoveFromFile("Examples/XML_Suppliers.xml", "SupplierID", id, RemoveSupplier);
						break;

					case 2:
						RemoveFromFile("Examples/XML_Products.xml", "ProductID", id, RemoveProduct);
						break;

					case 3:
						RemoveFromFile("Examples/XML_Shipments.xml", "ShipmentID", id, RemoveShipment);
						break;

					default:
						goto END;
				}

				break;

			case 3:

				fprintf(stdout, "Examples/XML_Suppliers.xml { 1 }\n");
				fprintf(stdout, "Examples/XML_Products.xml { 2 }\n");
				fprintf(stdout, "Examples/XML_Shipments.xml { 3 }\n\n");

				fprintf(stdout, "Choose table to modify: ");

				if (fscanf(stdin, "%d", &action_choice) != 1) {
					goto END;
				}

				fgetc(stdin);
				fprintf(stdout, "Enter ID to modify: ");

				if (fscanf(stdin, "%d", &id) != 1) {
					goto END;
				}

				fgetc(stdin);
				fprintf(stdout, BOLD("----------------------------------------------\n"));

				switch (action_choice) {

					case 1:
						ModifyTableContent("Examples/XML_Suppliers.xml", "SupplierID", id, ModifySupplier);
						break;

					case 2:
						ModifyTableContent("Examples/XML_Products.xml", "ProductID", id, ModifyProduct);
						break;

					case 3:
						ModifyTableContent("Examples/XML_Shipments.xml", "ShipmentID", id, ModifyShipment);
						break;

					default:
						goto END;
				}

				break;

			case 4:

				fprintf(stdout, "Examples/XML_Suppliers.xml { 1 }\n");
				fprintf(stdout, "Examples/XML_Products.xml { 2 }\n");
				fprintf(stdout, "Examples/XML_Shipments.xml { 3 }\n\n");

				fprintf(stdout, "Choose table to print: ");

				if (fscanf(stdin, "%d", &action_choice) != 1) {
					goto END;
				}

				fgetc(stdin);
				fprintf(stdout, BOLD("----------------------------------------------\n"));

				switch (action_choice) {

					case 1:
						PrintTable("Examples/XML_Suppliers.xml", PrintSuppliers);
						break;

					case 2:
						PrintTable("Examples/XML_Products.xml", PrintProducts);
						break;

					case 3:
						PrintTable("Examples/XML_Shipments.xml", PrintShipments);
						break;

					default:
						goto END;
				}

				break;

			case 5:

				fprintf(stdout, "Get all pairs of suppliers located in the same city. { 1 }\n");
				fprintf(stdout, "Determine the total number of suppliers participating in supply. { 2 }\n");
				fprintf(stdout,
				        "To calculate the total value of all products supplied by the supplier under the number ?. { 3 }\n");
				fprintf(stdout, "For each vendor specify the number and total volume of delivery in pieces. { 4 }\n");
				fprintf(stdout,
				        "Determine the colors of the products supplied by the supplier under the number ?. { 5 }\n\n");

				fprintf(stdout, "Choose request to database model: ");

				if (fscanf(stdin, "%d", &action_choice) != 1) {
					goto END;
				}

				fgetc(stdin);
				fprintf(stdout, BOLD("----------------------------------------------\n"));

				switch (action_choice) {

					case 1:
						GetCityLocalizedSuppliers();
						break;

					case 2:
						GetAllEngagedSuppliers();
						break;

					case 3:
						fprintf(stdout, "Enter SupplierID: ");

						if (fscanf(stdin, "%d", &id) != 1) {
							goto END;
						}

						fgetc(stdin);
						GetTotalProductCostBySupplier(id);
						break;

					case 4:
						GetAllSuppliersTotalProductsQuantity();
						break;

					case 5:
						fprintf(stdout, "Enter SupplierID: ");

						if (fscanf(stdin, "%d", &id) != 1) {
							goto END;
						}

						fgetc(stdin);
						GetProductColorBySupplier(id);
						break;

					default:
						goto END;
				}

				break;

			default:
			END:
				xmlCleanupMemory();
				xmlCleanupParser();
				return 0;
		}

		fprintf(stdout, BOLD("----------------------------------------------\n"));
	}
}