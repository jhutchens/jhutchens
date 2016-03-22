#Manipulating branches with git

####Creating a remote branch:

git checkout -b branchName

... edit files, add and commit ...

git push -u branchName


####Deleting a remote branch:

git push origin --delete branchName



####Merging a branch into master

1. Checkout the master branch: 

   git checkout master
   
2. Merge the branch into master: 

   git merge branchName


####Creating hardlinks in Windows

1. Run cmd as administrator 
2. Change directory to the location for the new link
3. To link a file...

	_mklink newLinkFileName "addressOfSourceFile"_

	Example: C:\...\NewLocationParentFolder> mklink new.txt "C:\...\source.txt"


4. To link an entire folder...

	_mklink /d newLinkFileName "addressOfSourceFile"_

	Example: C:\...\NewLocationParentFolder> mklink /d newFolder "C:\...\sourceFolder"

5. **Important!**

	If you are doing this for use with Git, **do not** create the link inside the GitHub folder on your computer.
	Git will not understand it, and will be unable to add/commit such files/folders. Instead, link _to_ the GitHub 
	folder _from_ your desired outside location.
	
	Example: C:\...\NewLocationParentFolder> mklink /d newFolder "C:\...\GitHub\yourItem"
