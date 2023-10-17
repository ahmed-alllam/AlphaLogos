# Contributing to AlphaLogos

Firstly, thank you for your interest in contributing to AlphaLogos! Follow the steps below to ensure a smooth contribution process.

## First-Time Setup

1. **Clone the repository**

   ```bash
   git clone https://github.com/ahmed-alllam/alphalogos.git
   cd alphalogos
   ```

2. **Install pre-commit using pip**

   ```bash
   pip install pre-commit
   ```

3. **Install the necessary pre-commit hooks**

   You can find detailed information about the commands [here](https://github.com/pocc/pre-commit-hooks#information-about-the-commands).

4. **Install the git pre-commit hooks**

   ```bash
   pre-commit install
   ```

## Regular Contribution Workflow

1. **Create an Issue**
   
   Before making any changes, create an issue via the GitHub UI explaining the desired edits, whether it's a feature request, bug report, test, or documentation enhancement. Make sure to explain the details thoroughly. You can create an issue [here](https://github.com/ahmed-alllam/alphalogos/issues). Assign the issue to yourself.

2. **Sync and Update your Local Repository**

   Open your terminal and navigate to the project folder.

   ```bash
   git pull origin main
   ```

   Ensure you are on the `main` branch.

   ```bash
   git checkout main
   ```

3. **Create a New Branch**

   Make sure the branch name meaningfully represents the feature or change you are working on.

   ```bash
   git checkout -b name_of_your_branch
   ```

4. **Start Coding**

   Make your edits and improvements to the codebase.

5. **Commit Your Changes**

   After making a chunk of edits or a significant progress:

   ```bash
   git add .
   git commit -m "Your meaningful commit message here"
   ```

6. **Push Your Changes**

   ```bash
   git push origin name_of_your_branch
   ```

7. **Create a Pull Request**

   After pushing your changes, visit the [AlphaLogos GitHub repository](https://github.com/ahmed-alllam/alphalogos). You should see a "Create Pull Request" button for your branch. Click it and provide detailed information about the changes you've made.

   In the PR, make sure to link it back to the issue you created initially. You can do this by writing:

   ```
   Resolves #IssueNumber
   ```

   Replace `IssueNumber` with the actual number of the issue you created.


## Handling Pre-commit Failures

If the pre-commit checks fail, don't worry! Pre-commit is designed to catch potential issues early in the development process. Here's what you should do:

1. **Fix the Issues**

   Review the error messages provided by pre-commit, and make the necessary changes to address them.

2. **Re-run pre-commit**

   Once you've fixed the issues, re-run pre-commit to ensure that your changes now pass the checks:

   ```bash
   pre-commit run --all-files
   ```

3. **Commit Your Changes**

   After ensuring that the checks pass, add your changes to the staging area, commit, and push to your branch as explained earlier:

   ```bash
   git add .
   git commit -m "Your meaningful commit message here"
   git push origin name_of_your_branch
   ```
---

Thank you for helping improve AlphaLogos! Your contributions are greatly appreciated.

---
