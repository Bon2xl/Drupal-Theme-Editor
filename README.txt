Stacks Editor
------------------------
Requires - Drupal 7


Block Sections
------------------------
- Page and regions | query hfeditor-container table
- Select theme | query theme table
- Display content type list | query content-type list
- Display styling for one content type | array list of block with classes based on block theme
- 

DB:
--------
hfeditor-container:
id
name
region
created
updated

hfeditor-blocks:
id
container ID - hf-container
css class
content type
node ID
weight


Logs:
--------
1h  Updated read me file and setup module container