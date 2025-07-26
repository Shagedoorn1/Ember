#!/bin/bash

# pushember.sh – Pushes Ember to GitHub
REPO_URL="https://github.com/Shagedoorn1/Ember.git"
FILES="Emberfile README.md Makefile include/ src/ examples/ test.sh"
COMMIT_MSG=${1:-"[X] Update Ember build tool"}

echo "[X] Verifying Git repo..."
if ! git rev-parse --is-inside-work-tree > /dev/null 2>&1; then
    echo "[!] Not a Git repository. Initializing..."
    git init
fi

CURRENT_URL=$(git remote get-url origin 2>/dev/null)
if [[ "$CURRENT_URL" != "$REPO_URL" ]]; then
    echo "[X] Setting correct remote for Ember..."
    git remote remove origin 2>/dev/null
    git remote add origin "$REPO_URL"
fi

echo "[X] Adding files..."
git add .

# Check if there are staged changes
if ! git diff --cached --quiet; then
    echo "[X] Committing with message: $COMMIT_MSG"
    git commit -m "$COMMIT_MSG"
else
    echo "[✓] Nothing to commit, working tree clean."
fi

# Pull with rebase only if working directory is clean
if git diff --quiet && git diff --cached --quiet; then
    echo "[X] Rebasing with remote..."
    git pull --rebase origin main || {
        echo "[!] Rebase failed. Resolve conflicts manually."
        exit 1
    }
else
    echo "[!] You have uncommitted or staged changes. Skipping pull to avoid conflicts."
fi

echo "[X] Pushing to origin/main..."
git branch -M main
git push -u origin main || {
    echo "[!] Push failed. You may need to manually pull and resolve conflicts."
    exit 1
}

echo "[✓] Ember push complete!"
