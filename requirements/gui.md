# GUI Requirements

## Main Window

### Menu Bar
* Add Transaction Button
* Import Button
* Export Button
* Delete Button

#### Add Transaction Button
* Left Click: invoke Add Transaction Window

#### Import Button
* Left Click: Import Procedure

#### Export Button
* Left Click: Export Procedure

#### Delete Button
* Left Click: Delete selected transactions ( Transaction rows with Select
  Checkbox checked)

### Filter Bar
* Filter Button Box
* Next Button
* Previous Button
* Add Filter Button

#### Filter Button Box
* Filter Buttons in horizontal layout

#### Add Filter Button
* Left Click: invoke Add Filter Window

#### Next Button
* Left Click: scroll to next page of Filter Buttons in the Filter Button Box

#### Previous Button
* Left Click: scroll to previous page of Filter Buttons in the Filter Button Box

#### Filter Button
* Left Click: invokes Apply Filter Procedure
* Right Click: invokes Filter Context Menu

#### Filter Context Menu
* Delete Filter Button - invokes Delete Filter Procedure

### Transaction Table
* ID Table Header
* Name Table Header
* Date Table Header
* Amount Table Header
* Transaction Table Rows

#### Transaction Table Row
* Select Checkbox
* ID Label
* Name Label
* Date Label
* Amount Label

##### Select Checkbox
Left Click: Check the box and highlight the row

### Import Procedure
* Invoke file browser to get file
* Parse file and check for errors
* Invoke Confirm Window with a comfirm-import message

### Export Procedure
* Invoke file browser to get save path
* Open file for writing
* Write filtered contents to file in csv format

### Apply Filter Procedure
* Query data using the selected filter
* Populate the Transaction Table with the results

### Delete Filter Procedure
* Remove filter from Filter Button Box
* Save changes to filter file

## Add Transaction Window
* Name Text Entry
* Date Label
* Amount Text Entry

### Name Text Entry
* Left Click: Give input focus to this

### Date Label
* Left Click: Open Calendar Widget

User selects date. Result goes into Date Label

### Amount Text Entry
* Left Click: Give input focus to this

Allow user to enter numbers only. 2 digits after the floating point. First
entered number starts in the 100ths place. Each new number moves the first
number one decimal place to the left.

ex. $0.01 -> $0.12 -> $1.23 -> $12.34

## Add Filter Window
* Name Text Entry
* Filter Parameter 1
* Filter Parameter 2
* Filter Parameter 3
* Add Button
* Cancel Button

### Filter Parameter
* Filter Parameter Type Dropdown
* Filter Parameter Entry

### Name Text Entry
Left Click: Give input focus to this

Allow user to enter text

### Filter Parameter Type Dropdown
* Left Click: Open dropdown menu

Options:
1. Name Contains - regular expression search through names
2. Date Between - find transactions between two dates
3. Amount Between - find transactions between amounts

### Filter Parameter Entry
Left Click: get input according to Filter Parameter Type selected

### Add Button
Left Click: invoke Add Filter Procedure

### Cancel Button
Left Click: Close the Add Filter Window

### Add Filter Procedure
Save the filter and add it to the Filter Button Box

## Confirm Window
* Message Label
* Confirm Button
* Cancel Button

### Message Label
Show the confirmation prompt

### Confirm Button
* Left Click: invoke Confirm Procedure with true

### Cancel Button
* Left Click: invoke the Confirm Procedure with false

### Confirm Procedure
Return the status of the operation to the caller (true/false) and close the
Confirm Window

