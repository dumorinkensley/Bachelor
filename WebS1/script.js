
function modify_qty(val,idElement) {
    var res = document.getElementById(idElement).value;
    var new_res = parseInt(res,10) + val;
    
    if (new_res < 0) {
        new_res = 0;
    }
    
    document.getElementById(idElement).value = new_res;
    return new_res;
}

