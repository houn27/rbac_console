# RBAC Console 
This is an RBAC (Role-Based Access Control) management tool developed using Qt (C++). It provides functionalities to query, add, delete, and edit entries in users, roles, and permissions tables in Mysql.

![](https://raw.githubusercontent.com/houn27/public-img/main/rbac_console_screenshot.png)

## My Setting
* Compiler: Apple clang version 14.0.0
* Qt version: qt 6.7.0

## Features
* Query users, roles, and permissions
* Add new users, roles, and permissions
* Delete existing users, roles, and permissions
* Edit details of users, roles, and permissions

## Highlights
* Utilizes `QSettings` to save database connections and table configurations.
* Enables operations on the mapping relationships between users, roles, and permissions.

## To improve
* Implement multi-threading to handle various database connections synchronously.
## Installation
#### Prerequisites
Qt 5.15 or later
```
# Example for Ubuntu
sudo apt-get install qt
# Example for Mac
brew install qt-mysql
```
#### Building the Project
```
# Open the project with Qt Creator or build from the command line
# Using qmake
qmake
make
```
#### Usage
```
# Run the executable
./sql_admin
```

