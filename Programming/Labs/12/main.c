#include "AddToFile.h"
#include "RemoveFromFile.h"
#include "ModifyTableContent.h"
#include "PrintTable.h"
#include "TaskFunctions.h"

int main(const int argc, const char* argv[]) {
	xmlInitParser();
	xmlKeepBlanksDefault(0);

	while (true) {

		fprintf(stdout, "1. Add to table\n");
		fprintf(stdout, "2. Remove from table\n");
		fprintf(stdout, "3. Modify table content\n");
		fprintf(stdout, "4. Print table\n");
		fprintf(stdout, "5. Request for database\n\n");

		int action_choice = 0;
		int id = 0;

		fprintf(stdout, "Enter your choice: ");

		if (fscanf(stdin, "%d", &action_choice) != 1) {
			goto END;
		}

		fgetc(stdin);
		fprintf(stdout, "----------------------------------------------\n");

		switch (action_choice) {

			case 1:

				fprintf(stdout, "1. Examples/XML_Suppliers.xml\n");
				fprintf(stdout, "2. Examples/XML_Products.xml\n");
				fprintf(stdout, "3. Examples/XML_Shipments.xml\n\n");

				fprintf(stdout, "Choose table to add to: ");

				if (fscanf(stdin, "%d", &action_choice) != 1) {
					goto END;
				}

				fgetc(stdin);
				fprintf(stdout, "----------------------------------------------\n");

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

				fprintf(stdout, "1. Examples/XML_Suppliers.xml\n");
				fprintf(stdout, "2. Examples/XML_Products.xml\n");
				fprintf(stdout, "3. Examples/XML_Shipments.xml\n\n");

				fprintf(stdout, "Choose table to remove from: ");

				if (fscanf(stdin, "%d", &action_choice) != 1) {
					goto END;
				}

				fgetc(stdin);
				fprintf(stdout, "Enter ID to remove: ");

				if (fscanf(stdin, "%d", &id) != 1) {
					goto END;
				}

				fprintf(stdout, "----------------------------------------------\n");

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

				fprintf(stdout, "1. Examples/XML_Suppliers.xml\n");
				fprintf(stdout, "2. Examples/XML_Products.xml\n");
				fprintf(stdout, "3. Examples/XML_Shipments.xml\n\n");

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
				fprintf(stdout, "----------------------------------------------\n");

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

				fprintf(stdout, "1. Examples/XML_Suppliers.xml\n");
				fprintf(stdout, "2. Examples/XML_Products.xml\n");
				fprintf(stdout, "3. Examples/XML_Shipments.xml\n\n");

				fprintf(stdout, "Choose table to print: ");

				if (fscanf(stdin, "%d", &action_choice) != 1) {
					goto END;
				}

				fgetc(stdin);
				fprintf(stdout, "----------------------------------------------\n");

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

				fprintf(stdout, "1. Get all pairs of suppliers located in the same city.\n");
				fprintf(stdout, "2. Determine the total number of suppliers participating in supply.\n");
				fprintf(stdout,
				        "3. To calculate the total value of all products supplied by the supplier under the number ?"
					        ".\n");
				fprintf(stdout, "4. For each vendor specify the number and total volume of delivery in pieces.\n");
				fprintf(stdout,
				        "5. Determine the colors of the products supplied by the supplier under the number ?.\n\n");

				fprintf(stdout, "Choose request to database model: ");

				if (fscanf(stdin, "%d", &action_choice) != 1) {
					goto END;
				}

				fgetc(stdin);
				fprintf(stdout, "----------------------------------------------\n");

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

		fprintf(stdout, "----------------------------------------------\n");
	}
}