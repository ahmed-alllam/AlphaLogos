expression_valid = false;
expression = "";

document.getElementById("analyzeFunction").onclick = function () {
    expression = document.getElementById("booleanFunction").value;
    expression_valid = false;

    fetch('/validate', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                expression: expression
            })
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

document.getElementById("truthTable").onclick = function () {
    if (expression_valid) {

        document.getElementById("output-title").innerHTML = "Truth Table";

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
                body: JSON.stringify({
                    expression: expression
                })
            })
            .then(response => {
                document.getElementById("loader").style.display = "none";

                if (response.status === 200) {
                    response.text().then(text => {
                        var truth_table_div = document.createElement("div");
                        truth_table_div.innerHTML = text;
                        truth_table_div.className = "truth-table";
                        document.getElementById("output").appendChild(truth_table_div);
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


function addPaddingToCanonicals() {
    const canonicalSoP = document.getElementById("sop");
    const canonicalPoS = document.getElementById("pos");

    if (!canonicalSoP || !canonicalPoS) {
        return;
    }

    canonicalSoP.innerHTML = canonicalSoP.innerHTML.replaceAll("+", "&nbsp; + &nbsp;");
    canonicalPoS.innerHTML = canonicalPoS.innerHTML.replaceAll(")(", ") &nbsp; (");
}

document.getElementById("canonicalForms").onclick = function () {
    if (expression_valid) {

        document.getElementById("output-title").innerHTML = "Canonical Forms";

        document.getElementById("validationMessage").innerHTML = "";
        document.getElementById("detailed-error-message").innerHTML = "";

        document.getElementById("output-options").style.display = "none";
        document.getElementById("inputSection").style.display = "none";
        document.getElementById("detailed-output").style.display = "flex";

        document.getElementById("loader").style.display = "block";

        fetch('/canonicals', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    expression: expression
                })
            })
            .then(response => {
                document.getElementById("loader").style.display = "none";

                if (response.status === 200) {
                    response.text().then(text => {
                        var canonicals_div = document.createElement("div");
                        canonicals_div.innerHTML = text;
                        canonicals_div.className = "canonical-forms";
                        document.getElementById("output").appendChild(canonicals_div);
                        addPaddingToCanonicals();
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

document.getElementById("primeImplicants").onclick = function () {
    if (expression_valid) {

        document.getElementById("output-title").innerHTML = "Prime Implicants";

        document.getElementById("validationMessage").innerHTML = "";
        document.getElementById("detailed-error-message").innerHTML = "";

        document.getElementById("output-options").style.display = "none";
        document.getElementById("inputSection").style.display = "none";
        document.getElementById("detailed-output").style.display = "flex";

        document.getElementById("loader").style.display = "block";

        fetch('/PI', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    expression: expression
                })
            })
            .then(response => {
                document.getElementById("loader").style.display = "none";

                if (response.status === 200) {
                    response.text().then(text => {
                        var primeImplicants_div = document.createElement("div");
                        primeImplicants_div.innerHTML = text;
                        primeImplicants_div.className = "prime-implicants";
                        document.getElementById("output").appendChild(primeImplicants_div);
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

document.getElementById("essentialPIs").onclick = function () {
    if (expression_valid) {

        document.getElementById("output-title").innerHTML = "Essential Prime Implicants";

        document.getElementById("validationMessage").innerHTML = "";
        document.getElementById("detailed-error-message").innerHTML = "";

        document.getElementById("output-options").style.display = "none";
        document.getElementById("inputSection").style.display = "none";
        document.getElementById("detailed-output").style.display = "flex";

        document.getElementById("loader").style.display = "block";

        fetch('/EPI', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    expression: expression
                })
            })
            .then(response => {
                document.getElementById("loader").style.display = "none";

                if (response.status === 200) {
                    response.text().then(text => {
                        var epi_div = document.createElement("div");
                        epi_div.innerHTML = text;
                        epi_div.className = "essential-prime-implicants";
                        document.getElementById("output").appendChild(epi_div);
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

document.getElementById("uncoveredMinterms").onclick = function () {
    if (expression_valid) {

        document.getElementById("output-title").innerHTML = "Uncovered Minterms";

        document.getElementById("validationMessage").innerHTML = "";
        document.getElementById("detailed-error-message").innerHTML = "";

        document.getElementById("output-options").style.display = "none";
        document.getElementById("inputSection").style.display = "none";
        document.getElementById("detailed-output").style.display = "flex";

        document.getElementById("loader").style.display = "block";

        fetch('/uncovered-minterms', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    expression: expression
                })
            })
            .then(response => {
                document.getElementById("loader").style.display = "none";

                if (response.status === 200) {
                    response.text().then(text => {
                        var uncovered_minterms_div = document.createElement("div");
                        uncovered_minterms_div.innerHTML = text;
                        uncovered_minterms_div.className = "uncovered-minterms";
                        document.getElementById("output").appendChild(uncovered_minterms_div);
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

document.getElementById("minimizedExpression").onclick = function () {
    if (expression_valid) {

        document.getElementById("output-title").innerHTML = "Minimized Expression";

        document.getElementById("validationMessage").innerHTML = "";
        document.getElementById("detailed-error-message").innerHTML = "";

        document.getElementById("output-options").style.display = "none";
        document.getElementById("inputSection").style.display = "none";
        document.getElementById("detailed-output").style.display = "flex";

        document.getElementById("loader").style.display = "block";

        fetch('/minimized-expression', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    expression: expression
                })
            })
            .then(response => {
                document.getElementById("loader").style.display = "none";

                if (response.status === 200) {
                    response.text().then(text => {
                        var minimized_expression_div = document.createElement("div");
                        minimized_expression_div.innerHTML = text;
                        minimized_expression_div.className = "minimal-expression";
                        document.getElementById("output").appendChild(minimized_expression_div);
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

function removeLabels(obj) {
    for (let key in obj) {
        if (typeof obj[key] === 'object' && obj[key] !== null) {
            // Recursively check nested objects
            removeLabels(obj[key]);
        }
        if (key === 'label' && typeof obj[key] === 'string' && obj[key].includes('$')) {
            delete obj[key];
        }
    }
}

function displayVerilogCode(div, code) {
    div.innerHTML = "";
    const container = document.createElement('div');
    container.className = 'circuit-container';
    container.id = 'circuit-container';
    div.appendChild(container);

    const jsonCode = JSON.parse(code);

    // remove all labels (nested) in json that contain $
    removeLabels(jsonCode);

    setTimeout(() => {
        const circuit = new digitaljs.Circuit(jsonCode);
        circuit.displayOn($('#circuit-container'));
        circuit.start();
    }, 0);
}

document.getElementById("logicCircuit").onclick = function () {
    if (expression_valid) {

        document.getElementById("output-title").innerHTML = "Logic Circuit";

        document.getElementById("validationMessage").innerHTML = "";
        document.getElementById("detailed-error-message").innerHTML = "";

        document.getElementById("output-options").style.display = "none";
        document.getElementById("inputSection").style.display = "none";
        document.getElementById("detailed-output").style.display = "flex";

        document.getElementById("loader").style.display = "block";

        fetch('/draw-circuit', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    expression: expression
                })
            })
            .then(response => {
                document.getElementById("loader").style.display = "none";

                if (response.status === 200) {
                    response.text().then(text => {
                        var circuit_div = document.createElement("div");
                        displayVerilogCode(circuit_div, text);
                        circuit_div.className = "logic-circuit";
                        document.getElementById("output").appendChild(circuit_div);
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

document.getElementById("KMap").onclick = function () {
    if (expression_valid) {

        document.getElementById("output-title").innerHTML = "Karnaugh Map";

        document.getElementById("validationMessage").innerHTML = "";
        document.getElementById("detailed-error-message").innerHTML = "";

        document.getElementById("output-options").style.display = "none";
        document.getElementById("inputSection").style.display = "none";
        document.getElementById("detailed-output").style.display = "flex";

        document.getElementById("loader").style.display = "block";

        fetch('/draw-kmap', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    expression: expression
                })
            })
            .then(response => {
                document.getElementById("loader").style.display = "none";

                if (response.status === 200) {
                    response.text().then(text => {
                        var kmap_div = document.createElement("div");
                        kmap_div.className = "kmap-container";
                        kmap_div.innerHTML = text;
                        document.getElementById("output").appendChild(kmap_div);
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

document.getElementById("back").onclick = function () {
    document.getElementById("output-options").style.display = "grid";
    document.getElementById("detailed-output").style.display = "none";
    document.getElementById("inputSection").style.display = "flex";


    // Remove truth table
    var truth_table_div = document.getElementsByClassName("truth-table")[0];
    if (truth_table_div) {
        truth_table_div.remove();
    }

    // Remove canonical forms
    var canonicals_div = document.getElementsByClassName("canonical-forms")[0];
    if (canonicals_div) {
        canonicals_div.remove();
    }

    // Remove prime implicants
    var primeImplicants_div = document.getElementsByClassName("prime-implicants")[0];
    if (primeImplicants_div) {
        primeImplicants_div.remove();
    }

    // Remove essential prime implicants
    var epi_div = document.getElementsByClassName("essential-prime-implicants")[0];
    if (epi_div) {
        epi_div.remove();
    }

    // Remove uncovered minterms
    var uncovered_minterms_div = document.getElementsByClassName("uncovered-minterms")[0];
    if (uncovered_minterms_div) {
        uncovered_minterms_div.remove();
    }

    // Remove minimized expression
    var minimized_expression_div = document.getElementsByClassName("minimal-expression")[0];
    if (minimized_expression_div) {
        minimized_expression_div.remove();
    }

    // Remove logic circuit
    var circuit_div = document.getElementsByClassName("logic-circuit")[0];
    if (circuit_div) {
        circuit_div.remove();
    }

    // Remove KMap
    var kmap_div = document.getElementsByClassName("kmap-container")[0];
    if (kmap_div) {
        kmap_div.remove();
    }

    // remove other elements from detailed output...

    return false;
}

function downloadURI(uri, name) {
    var link = document.createElement("a");
    link.download = name;
    link.href = uri;
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link); // Clean up after downloading
}

document.getElementById("download").addEventListener("click", function () {
    var div = document.getElementById("output");

    if (div.children.length == 0) {
        return false;
    }

    // check if style contains overflow: scroll
    if (div.children[0].style.overflow != "scroll") {
        div = div.children[0].children[0];
    } else {
        div = div.children[0];
    }

    // make it handle scrollable divs
    domtoimage.toPng(div, {
            width: div.scrollWidth,
            height: div.scrollHeight
        })
        .then(function (dataUrl) {
            downloadURI(dataUrl, "alpha-logos-output.png");
        })
        .catch(function (error) {
            console.error('Error:', error);
        });

    return false;
});