
expression_valid = false;
expression = "";

document.getElementById("analyzeFunction").onclick = function() {
    expression = document.getElementById("booleanFunction").value;
    expression_valid = false;

    fetch('/validate', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({expression: expression})
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
        } else {
            document.getElementById("validationMessage").innerHTML = "An error occurred.";
            document.getElementById("validationMessage").style.color = "red";

            expression_valid = false;
        }
    })
    .catch((error) => {
        console.error('Error:', error);

        document.getElementById("validationMessage").innerHTML = "An error occurred.";
        document.getElementById("validationMessage").style.color = "red";
        expression_valid = false;
    });

    return false;
}

document.getElementById("truthTable").onclick = function() {
    if (expression_valid) {
        document.getElementById("validationMessage").innerHTML = "";
        document.getElementById("detailed-error-message").innerHTML = "";

        document.getElementById("output-options").style.display = "none";
        document.getElementById("inputSection").style.display = "none";
        document.getElementById("detailed-output").style.display = "flex";

        document.getElementById("loader").style.display = "block";

        fetch('/truth-table', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({expression: expression})
        })
        .then(response => {
            document.getElementById("loader").style.display = "none";

            if (response.status === 200) {
                response.text().then(text => {
                    var truth_table_div = document.createElement("div");
                    truth_table_div.innerHTML = text;
                    truth_table_div.className = "truth-table";
                    document.getElementById("detailed-output").appendChild(truth_table_div);
                });
            } else if (response.status === 400) {
                response.text().then(text => {
                    document.getElementById("detailed-error-message").innerHTML = text;
                });
            } else {
                document.getElementById("detailed-error-message").innerHTML = "An error occurred.";
            }
        })
        .catch((error) => {
            console.error('Error:', error);
            document.getElementById("loader").style.display = "none";
            document.getElementById("detailed-error-message").innerHTML = "An error occurred.";
        });
    } else {
        document.getElementById("validationMessage").innerHTML = "Enter Valid Expression and Analyze";
        document.getElementById("validationMessage").style.color = "red";
    }

    return false;
}

document.getElementById("back").onclick = function() {
    document.getElementById("output-options").style.display = "grid";
    document.getElementById("detailed-output").style.display = "none";
    document.getElementById("inputSection").style.display = "flex";


    // Remove truth table
    var truth_table_div = document.getElementsByClassName("truth-table")[0];
    if (truth_table_div) {
        truth_table_div.remove();
    }

    // remove other elements from detailed output...

    return false;
}