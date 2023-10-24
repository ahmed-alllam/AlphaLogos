
expression_valid = false;

document.getElementById("analyzeFunction").onclick = function() {
    fetch('/validate', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({expression: document.getElementById("booleanFunction").value})
    })
    .then(response => {
        if (response.status === 200) {
            response.text().then(text => {
                document.getElementById("validationMessage").innerHTML = text;
                document.getElementById("validationMessage").style.color = "green";
            });

            expression_valid = true;
        } else if (response.status === 400) {
            response.text().then(text => {
                document.getElementById("validationMessage").innerHTML = text;
                document.getElementById("validationMessage").style.color = "red";
            });

            expression_valid = false;
        }
    })
    .catch((error) => {
        console.error('Error:', error);

        expression_valid = false;
    });

    return false;
}