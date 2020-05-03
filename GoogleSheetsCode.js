function doGet(e) { 
  Logger.log( JSON.stringify(e) );  // view parameters

  var result = 'Received'; // assume success

  if (e.parameter= undefined) {
    result = 'No Parameters';
  }
  else {
    
    var id = '1zEmMYtPzq34f4yLwSeZN0tuJcd9gCqj5b_3ktz_7QEY'; // Spreadsheet ID
    var sheet = SpreadsheetApp.openById(id).getActiveSheet();
    var newRow = sheet.getLastRow() + 1;
    var rowData = [];
    
    rowData[0] = new Date(); // Timestamp in column A
    rowData[0] = Utilities.formatDate(rowData[0], "GMT-04:00", "MM/dd/yy, h:mm a");

    for (var param in e.parameter) {
      Logger.log('In for loop, param='+param);
      var value = stripQuotes(e.parameter[param]);
      var datas = value.split(':');

      switch (param) {
          
        case 'device1': //Parameter
          rowData[1] = datas[0]; //Value in column B
          rowData[2] = datas[1];
          rowData[3] = datas[2];
          rowData[4] = datas[4];
          break;
          
        case 'device2': //Parameter
          rowData[2] = value; //Value in column C
          break;
          
        case 'device3': //Parameter
          rowData[3] = value; //Value in column D
          break;
          
        case 'device4': //Parameter
          rowData[4] = value; //Value in column E
          break;
          
        case 'device5': //Parameter
          rowData[5] = value; //Value in column F
          break;
          
        case 'device6': //Parameter
          rowData[6] = value; //Value in column G
          break;
          
        case 'device7': //Parameter
          rowData[7] = value; //Value in column H
          break;  
          
        case 'device8': //Parameter
          rowData[8] = value; //Value in column I
          break;  
          
        case 'device9': //Parameter
          rowData[9] = value; //Value in column J
          break; 
          
        case 'device10': //Parameter
          rowData[10] = value; //Value in column K
          break;   

        default:
          result = "unsupported parameter";
      }
    }
    Logger.log(JSON.stringify(rowData));

    // Write new row below
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }

  // Return result of operation
  return ContentService.createTextOutput(result);
}

/*
* Remove leading and trailing single or double quotes
*/
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}