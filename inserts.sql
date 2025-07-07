-- Customers
INSERT INTO Customer (customer_id, name, account_tier) VALUES
('CUST001', 'V', 'Platinum'),
('CUST002', 'Johnny Silverhand', 'Chrome'),
('CUST003', 'Judy Alvarez', 'Gold'),
('CUST004', 'Panam Palmer', 'Gold'),
('CUST005', 'Jackie Welles', 'Chrome');

-- Products
INSERT INTO Product (product_id, item_name, model_number) VALUES
('PROD001', 'Sandevistan', 9001),
('PROD002', 'Gorilla Arms', 2077),
('PROD003', 'Monowire', 42),
('PROD004', 'Kerenzikov', 2020),
('PROD005', 'Projectile Launch System', 1337);

-- Purchases
INSERT INTO Purchase (purchase_id, customer_id, product_id, purchase_date) VALUES
('PURCH001', 'CUST001', 'PROD001', '2077-10-23'),
('PURCH002', 'CUST002', 'PROD002', '2077-05-11'),
('PURCH003', 'CUST003', 'PROD003', '2077-08-19'),
('PURCH004', 'CUST004', 'PROD004', '2077-01-01'),
('PURCH005', 'CUST005', 'PROD005', '2077-12-25');

-- Appointments
INSERT INTO Appointment (appointment_id, customer_id, product_id, appointment_date) VALUES
('APP001', 'CUST001', 'PROD001', '2077-10-24'),
('APP002', 'CUST002', 'PROD002', '2077-05-12'),
('APP003', 'CUST003', 'PROD003', '2077-08-20'),
('APP004', 'CUST004', 'PROD004', '2077-01-02'),
('APP005', 'CUST005', 'PROD005', '2077-12-26');

-- Installations
INSERT INTO Installation (installation_id, customer_id, product_id, installation_date) VALUES
('INST001', 'CUST001', 'PROD001', '2077-10-25'),
('INST002', 'CUST002', 'PROD002', '2077-05-13'),
('INST003', 'CUST003', 'PROD003', '2077-08-21'),
('INST004', 'CUST004', 'PROD004', '2077-01-03'),
('INST005', 'CUST005', 'PROD005', '2077-12-27');
