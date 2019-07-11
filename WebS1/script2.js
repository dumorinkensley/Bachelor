function modify_qt(val) {
    var qt = document.getElementById('qt').value;
    var new_qt = parseInt(qty,10) + val;
    
    if (new_qty < 0) {
        new_qty = 0;
    }
    
    document.getElementById('qt').value = new_qt;
    return new_qt;
}