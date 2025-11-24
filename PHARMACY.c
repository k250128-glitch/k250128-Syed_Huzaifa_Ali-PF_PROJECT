#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Medicine {
    int id;
    char name[50];
    char company[50];
    int quantity;
    float price;
    char expiry[15];
};

struct Supplier {
    int id;
    char name[50];
    char company[50];
    char contact[20];
};

struct Customer {
    int id;
    char name[50];
    char contact[20];
    char address[100];
};



// FUNCTION DECLARATIONS


// Medicine
void addMedicine();
void displayMedicine();
void searchMedicine();
void updateMedicine();
void deleteMedicine();

// Supplier
void addSupplier();
void displaySupplier();
void searchSupplier();
void updateSupplier();
void deleteSupplier();

// Customer
void addCustomer();
void displayCustomer();
void searchCustomer();
void updateCustomer();
void deleteCustomer();


// --------------------------------------------
// MAIN MENU
// --------------------------------------------
int main() {
    int choice;

    while (1) {
        printf("\n================== PHARMACY MANAGEMENT SYSTEM ==================\n");
        printf("1. Medicine Management\n");
        printf("2. Supplier Management\n");
        printf("3. Customer Management\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int m;
                while (1) {

                    printf("\n--- Medicine Menu ---\n");
                    printf("1. Add Medicine\n");
                    printf("2. Display All Medicines\n");
                    printf("3. Search Medicine\n");
                    printf("4. Update Medicine\n");
                    printf("5. Delete Medicine\n");
                    printf("6. Back\n");
                    printf("Choose: ");
                    scanf("%d", &m);

                    if (m == 1) addMedicine();
                    else if (m == 2) displayMedicine();
                    else if (m == 3) searchMedicine();
                    else if (m == 4) updateMedicine();
                    else if (m == 5) deleteMedicine();
                    else if (m == 6) break;
                    else printf("Invalid!\n");

                }
                break;
            }

            case 2: {
                int s;
                while (1) {

                    printf("\n--- Supplier Menu ---\n");
                    printf("1. Add Supplier\n");
                    printf("2. Display All Suppliers\n");
                    printf("3. Search Supplier\n");
                    printf("4. Update Supplier\n");
                    printf("5. Delete Supplier\n");
                    printf("6. Back\n");
                    printf("Choose: ");
                    scanf("%d", &s);

                    if (s == 1) addSupplier();
                    else if (s == 2) displaySupplier();
                    else if (s == 3) searchSupplier();
                    else if (s == 4) updateSupplier();
                    else if (s == 5) deleteSupplier();
                    else if (s == 6) break;
                    else printf("Invalid!\n");

                }
                break;
            }

            case 3: {
                int c;
                while (1) {
                    printf("\n--- Customer Menu ---\n");
                    printf("1. Add Customer\n");
                    printf("2. Display All Customers\n");
                    printf("3. Search Customer\n");
                    printf("4. Update Customer\n");
                    printf("5. Delete Customer\n");
                    printf("6. Back\n");
                    printf("Choose: ");
                    scanf("%d", &c);

                    if (c == 1) addCustomer();
                    else if (c == 2) displayCustomer();
                    else if (c == 3) searchCustomer();
                    else if (c == 4) updateCustomer();
                    else if (c == 5) deleteCustomer();
                    else if (c == 6) break;
                    else printf("Invalid!\n");

                }
                break;
            }

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}


// --------------------------------------------------------
// MEDICINE MANAGEMENT
// --------------------------------------------------------
void addMedicine() {
    struct Medicine m;

    printf("\nEnter ID: ");
    scanf("%d", &m.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", m.name);

    printf("Enter Company: ");
    scanf(" %[^\n]", m.company);

    printf("Enter Quantity: ");
    scanf("%d", &m.quantity);

    printf("Enter Price: ");
    scanf("%f", &m.price);

    printf("Enter Expiry (DD/MM/YYYY): ");
    scanf(" %[^\n]", m.expiry);

    FILE *fp = fopen("medicine.dat", "ab");
    fwrite(&m, sizeof(m), 1, fp);
    fclose(fp);

    printf("\nMedicine Added Successfully!\n");
}

void displayMedicine() {
    struct Medicine m;
    FILE *fp = fopen("medicine.dat", "rb");

    if (!fp) {
        printf("No data found.\n");
        return;
    }

    printf("\n--- Medicine List ---\n");

    while (fread(&m, sizeof(m), 1, fp) == 1) {
        printf("\nID: %d\n", m.id);
        printf("Name: %s\n", m.name);
        printf("Company: %s\n", m.company);
        printf("Quantity: %d\n", m.quantity);
        printf("Price: %.2f\n", m.price);
        printf("Expiry: %s\n", m.expiry);

        if (m.quantity < 5)
            printf(" LOW STOCK!\n");
    }

    fclose(fp);
}

void searchMedicine() {
    struct Medicine m;
    int id, found = 0;

    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    FILE *fp = fopen("medicine.dat", "rb");

    while (fread(&m, sizeof(m), 1, fp) == 1) {
        if (m.id == id) {
            found = 1;

            printf("\n--- Medicine Found ---\n");
            printf("ID: %d\n", m.id);
            printf("Name: %s\n", m.name);
            printf("Company: %s\n", m.company);
            printf("Quantity: %d\n", m.quantity);
            printf("Price: %.2f\n", m.price);
            printf("Expiry: %s\n", m.expiry);
        }
    }

    if (!found)
        printf("Not found.\n");

    fclose(fp);
}

void updateMedicine() {
    struct Medicine m;
    int id, found = 0;

    printf("\nEnter ID to update: ");
    scanf("%d", &id);

    FILE *fp = fopen("medicine.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    while (fread(&m, sizeof(m), 1, fp) == 1) {
        if (m.id == id) {
            found = 1;
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", m.name);
            printf("Enter New Company: ");
            scanf(" %[^\n]", m.company);
            printf("Enter New Quantity: ");
            scanf("%d", &m.quantity);
            printf("Enter New Price: ");
            scanf("%f", &m.price);
            printf("Enter New Expiry: ");
            scanf(" %[^\n]", m.expiry);
        }
        fwrite(&m, sizeof(m), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("medicine.dat");
    rename("temp.dat", "medicine.dat");

    if (found)
        printf("Updated successfully!\n");
    else
        printf("ID not found.\n");
}

void deleteMedicine() {
    struct Medicine m;
    int id, found = 0;

    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen("medicine.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    while (fread(&m, sizeof(m), 1, fp) == 1) {
        if (m.id == id) {
            found = 1;
            continue;
        }
        fwrite(&m, sizeof(m), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("medicine.dat");
    rename("temp.dat", "medicine.dat");

    if (found)
        printf("Deleted successfully!\n");
    else
        printf("ID not found.\n");
}



// --------------------------------------------------------
// SUPPLIER MANAGEMENT
// --------------------------------------------------------
void addSupplier() {
    struct Supplier s;

    printf("\nEnter ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Company: ");
    scanf(" %[^\n]", s.company);

    printf("Enter Contact: ");
    scanf(" %[^\n]", s.contact);

    FILE *fp = fopen("supplier.dat", "ab");
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Supplier Added!\n");
}

void displaySupplier() {
    struct Supplier s;
    FILE *fp = fopen("supplier.dat", "rb");

    if (!fp) {
        printf("No data.\n");
        return;
    }

    printf("\n--- Supplier List ---\n");

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("\nID: %d\n", s.id);
        printf("Name: %s\n", s.name);
        printf("Company: %s\n", s.company);
        printf("Contact: %s\n", s.contact);
    }

    fclose(fp);
}

void searchSupplier() {
    struct Supplier s;
    int id, found = 0;

    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    FILE *fp = fopen("supplier.dat", "rb");

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.id == id) {
            found = 1;
            printf("\n--- Supplier Found ---\n");
            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.name);
            printf("Company: %s\n", s.company);
            printf("Contact: %s\n", s.contact);
        }
    }

    if (!found)
        printf("Not found.\n");

    fclose(fp);
}

void updateSupplier() {
    struct Supplier s;
    int id, found = 0;

    printf("\nEnter ID to update: ");
    scanf("%d", &id);

    FILE *fp = fopen("supplier.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.id == id) {
            found = 1;
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Company: ");
            scanf(" %[^\n]", s.company);
            printf("Enter New Contact: ");
            scanf(" %[^\n]", s.contact);
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("supplier.dat");
    rename("temp.dat", "supplier.dat");

    if (found)
        printf("Updated!\n");
    else
        printf("ID not found.\n");
}

void deleteSupplier() {
    struct Supplier s;
    int id, found = 0;

    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen("supplier.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.id == id) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("supplier.dat");
    rename("temp.dat", "supplier.dat");

    if (found)
        printf("Deleted!\n");
    else
        printf("ID not found.\n");
}



// --------------------------------------------------------
// CUSTOMER MANAGEMENT
// --------------------------------------------------------
void addCustomer() {
    struct Customer c;

    printf("\nEnter ID: ");
    scanf("%d", &c.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", c.name);

    printf("Enter Contact: ");
    scanf(" %[^\n]", c.contact);

    printf("Enter Address: ");
    scanf(" %[^\n]", c.address);

    FILE *fp = fopen("customer.dat", "ab");
    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);

    printf("Customer Added!\n");
}

void displayCustomer() {
    struct Customer c;
    FILE *fp = fopen("customer.dat", "rb");

    if (!fp) {
        printf("No data.\n");
        return;
    }

    printf("\n--- Customer List ---\n");

    while (fread(&c, sizeof(c), 1, fp) == 1) {
        printf("\nID: %d\n", c.id);
        printf("Name: %s\n", c.name);
        printf("Contact: %s\n", c.contact);
        printf("Address: %s\n", c.address);
    }

    fclose(fp);
}

void searchCustomer() {
    struct Customer c;
    int id, found = 0;

    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    FILE *fp = fopen("customer.dat", "rb");

    while (fread(&c, sizeof(c), 1, fp) == 1) {
        if (c.id == id) {
            found = 1;
            printf("\n--- Customer Found ---\n");
            printf("ID: %d\n", c.id);
            printf("Name: %s\n", c.name);
            printf("Contact: %s\n", c.contact);
            printf("Address: %s\n", c.address);
        }
    }

    if (!found)
        printf("Not found.\n");

    fclose(fp);
}

void updateCustomer() {
    struct Customer c;
    int id, found = 0;

    printf("\nEnter ID to update: ");
    scanf("%d", &id);

    FILE *fp = fopen("customer.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    while (fread(&c, sizeof(c), 1, fp) == 1) {
        if (c.id == id) {
            found = 1;
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", c.name);
            printf("Enter New Contact: ");
            scanf(" %[^\n]", c.contact);
            printf("Enter New Address: ");
            scanf(" %[^\n]", c.address);
        }
        fwrite(&c, sizeof(c), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("customer.dat");
    rename("temp.dat", "customer.dat");

    if (found)
        printf("Updated!\n");
    else
        printf("ID not found.\n");
}

void deleteCustomer() {
    struct Customer c;
    int id, found = 0;

    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen("customer.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    while (fread(&c, sizeof(c), 1, fp) == 1) {
        if (c.id == id) {
            found = 1;
            continue;
        }
        fwrite(&c, sizeof(c), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("customer.dat");
    rename("temp.dat", "customer.dat");

    if (found)
        printf("Deleted!\n");
    else
        printf("ID not found.\n");
}

