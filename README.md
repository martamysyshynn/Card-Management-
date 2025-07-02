# 💳 Card Management System

## Description

This is a console-based C++ application that simulates a simple card management system. It allows users to create and manage debit or credit cards, while administrators can view and block user cards. Data is stored in plain text files.

## Features

### 👤 User:
- Sign up / Sign in
- Add debit or credit cards
- View all cards
- View balance on a specific card
- Change card password
- Withdraw funds (with fee for credit cards)
- Deposit money (with cashback for debit cards)

### 🛡️ Admin:
- Sign up / Sign in
- View all user card data
- Block a user’s card

## 📁 Data Files

- `personsData.txt`: stores user/admin credentials and phone/ID numbers
- `personsCards.txt`: stores card details including card name, number, CVV, balance, and password

> ⚠️ **Important:** All data is stored in plain text. Do **not** use real card or personal data.


## Example

```
-------------------✨CARD MANAGMENT!✨-------------------

 -------------------Menu-------------------
1. Register as an Admin
2. Register as a User
3. Login as an Admin
4. Login as a User
5. Exit
Enter your choice:
```

## Limitations

- No encryption — all data is readable in `.txt` files.
- Basic console interface (no GUI).
- No persistent user session.
- Only "credit" or "debit" card types are supported (exact strings).

## License

This project is for educational. No license.
