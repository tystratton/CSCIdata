-- Customer Table
CREATE TABLE Customer (
    customer_id VARCHAR(255) PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    account_tier VARCHAR(255)
);

-- Product Table
CREATE TABLE Product (
    product_id VARCHAR(255) PRIMARY KEY,
    item_name VARCHAR(255) NOT NULL,
    model_number INT
);

-- Purchase Table
CREATE TABLE Purchase (
    purchase_id VARCHAR(255) PRIMARY KEY,
    customer_id VARCHAR(255),
    product_id VARCHAR(255),
    purchase_date DATE,
    FOREIGN KEY (customer_id) REFERENCES Customer(customer_id),
    FOREIGN KEY (product_id) REFERENCES Product(product_id)
);

-- Appointment Table
CREATE TABLE Appointment (
    appointment_id VARCHAR(255) PRIMARY KEY,
    customer_id VARCHAR(255),
    product_id VARCHAR(255),
    appointment_date DATE,
    FOREIGN KEY (customer_id) REFERENCES Customer(customer_id),
    FOREIGN KEY (product_id) REFERENCES Product(product_id)
);

-- Installation Table
CREATE TABLE Installation (
    installation_id VARCHAR(255) PRIMARY KEY,
    customer_id VARCHAR(255),
    product_id VARCHAR(255),
    installation_date DATE,
    FOREIGN KEY (customer_id) REFERENCES Customer(customer_id),
    FOREIGN KEY (product_id) REFERENCES Product(product_id)
);
