# GUI Requirements

## Main Window

### Menu Bar
* Add Transaction Button
* Import Button
* Export Button

#### Add Transaction Button
* Left Click: invoke Add Transaction Window

#### Import Button
* Left Click: Import Procedure

#### Export Button
* Left Click: Export Procedure

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

## Add Filter Window

## Confirm Window

