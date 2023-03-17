// TODO PAGE //

// TODO VARIABLES //
var currentTodos = [];
var completedTodos = 0;
var todoTableRowIDs = 0;

// TODO FUNCTIONS //

function addTodo(memoryList){
    // create table row from input
    let table = document.getElementById("tableTodo");
    let row = table.insertRow(-1);
    row.id = todoTableRowIDs;

    // define each cell to its position in new row
    let rowDate = row.insertCell(0);
    let rowTime = row.insertCell(1);
    let rowDescription = row.insertCell(2);
    let rowFor = row.insertCell(3);
    let rowDone = row.insertCell(4);
    // add checkbox to table and pass row ID to deleteRow function on click
    let checkBox = ('<input type="checkbox" id="todoIsDone" onclick="deleteRow(parentNode.parentNode)">');

    // Check if populating from input field or memory
    if (arguments[0] != null){
        // fill each created cell with content
        rowDate.innerHTML = memoryList[0];
        rowTime.innerHTML = memoryList[1];
        rowDescription.innerHTML = memoryList[2];

        // Check checkbox to determine for who
        if (memoryList[3] == "Andrea"){
            rowFor.innerHTML = "Andrea";
        }
        else if (memoryList[3] == "Thomas"){
            rowFor.innerHTML = "Thomas";
        }
        else if (memoryList[3] == "Andrea & Thomas"){
            rowFor.innerHTML = "Andrea & Thomas";
        }
        else {
            rowFor.innerHTML = "-";
        }
        rowDone.innerHTML = checkBox;
        todoTableRowIDs += 1;
    }
    else{
        // save current input to list of current todos
        let tempoList = []
        tempoList.push(document.getElementById("todoDate").value);
        tempoList.push(document.getElementById("todoTime").value);
        tempoList.push(document.getElementById("todoDescrip").value);

        // fill each created cell with content
        rowDate.innerHTML = document.getElementById("todoDate").value;
        rowTime.innerHTML = document.getElementById("todoTime").value;
        rowDescription.innerHTML = document.getElementById("todoDescrip").value;

        // Check checkbox to determine for who
        if (document.getElementById("isAndrea").checked == true){
            rowFor.innerHTML = "Andrea";
            tempoList.push("Andrea");
        }
        else if (document.getElementById("isThomas").checked == true){
            rowFor.innerHTML = "Thomas";
            tempoList.push("Thomas");
        }
        else if (document.getElementById("isBoth").checked == true){
            rowFor.innerHTML = "Andrea & Thomas";
            tempoList.push("Andrea & Thomas");
        }
        else {
            rowFor.innerHTML = "-";
        }
        rowDone.innerHTML = checkBox;
        currentTodos.push(tempoList);
        todoTableRowIDs += 1;
    }
    saveTodoToMemory();
    clearInput();
}

function clearInput(){
    // clear all input fields
    document.getElementById("todoDate").value = "";
    document.getElementById("todoTime").value = "";
    document.getElementById("todoDescrip").value = "";
    document.getElementById("isAndrea").checked = false;
    document.getElementById("isThomas").checked = false;
    document.getElementById("isBoth").checked = false;
}


function deleteRow(element){
    // delete current row by row ID
    let row = document.getElementById(element.id);
    let deleteList = [];
    // add items from row to tempo list
    deleteList.push(row.children[0].textContent);
    deleteList.push(row.children[1].textContent);
    deleteList.push(row.children[2].textContent);
    deleteList.push(row.children[3].textContent);
    // compare item in deleteList to currentTodosList, find list and delete
    for (var i = 0; i < currentTodos.length; i++){
        if (JSON.stringify(deleteList) === JSON.stringify(currentTodos[i])){
            currentTodos.pop(currentTodos[i]);
        }
    }
    // remove row from table
    row.remove();
    // increment completed counter
    completedTodos += 1;
}

function loadTodoFromMemory(){
    // load array from local storage
    var currentTodos = JSON.parse(localStorage.getItem('todo'));
    for (var i = 0; i < currentTodos.length; i++){
        addTodo(currentTodos[i]);
    }
}

function saveTodoToMemory(){
    // save todo array to local storage
    localStorage.setItem('todo', JSON.stringify(currentTodos));
}

function checkBoxControl(self){
    // allow only one checbox to be active
    if (self.id == "isAndrea"){
        document.getElementById("isThomas").checked = false;
        document.getElementById("isBoth").checked = false;
    }
    else if (self.id == "isThomas"){
        document.getElementById("isAndrea").checked = false;
        document.getElementById("isBoth").checked = false;
    }
    else{
        document.getElementById("isAndrea").checked = false;
        document.getElementById("isThomas").checked = false;
    }
}