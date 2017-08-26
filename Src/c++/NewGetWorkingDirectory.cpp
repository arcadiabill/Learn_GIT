bool getcwd(std::string& path)
  {
    typedef std::pair<dev_t, ino_t> file_id;
    
    bool success = false;
    int start_fd = open(".", O_RDONLY); //Keep track of start directory, so can jump back to it later
    if (start_fd != -1)
    {
      struct stat sb;
      if (!fstat(start_fd, &sb))
      {
        file_id current_id(sb.st_dev, sb.st_ino);
        if (!stat("/", &sb)) //Get info for root directory, so we can determine when we hit it
        {
          std::vector<std::string> path_components;
          file_id root_id(sb.st_dev, sb.st_ino);

          while (current_id != root_id) //If they're equal, we've obtained enough info to build the path
          {
            bool pushed = false;

            if (!chdir("..")) //Keep recursing towards root each iteration
            {
              DIR *dir = opendir(".");
              if (dir)
              {
                dirent *entry;
                while ((entry = readdir(dir))) //We loop through each entry trying to find where we came from
                {
                  if ((strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..") && !lstat(entry->d_name, &sb)))
                  {
                    file_id child_id(sb.st_dev, sb.st_ino);
                    if (child_id == current_id) //We found where we came from, add its name to the list
                    {
                      path_components.push_back(entry->d_name);
                      pushed = true;
                      break;
                    }
                  }
                }
                closedir(dir);

                if (pushed && !stat(".", &sb)) //If we have a reason to contiue, we update the current dir id
                {
                  current_id = file_id(sb.st_dev, sb.st_ino);
                }
              }//Else, Uh oh, can't read information at this level
            }
            if (!pushed) { break; } //If we didn't obtain any info this pass, no reason to continue
          }

          if (current_id == root_id) //Unless they're equal, we failed above
          {
            //Built the path, will always end with a slash
            path = "/";
            for (std::vector<std::string>::reverse_iterator i = path_components.rbegin(); i != path_components.rend(); ++i)
            {
              path += *i+"/";
            }
            success = true;
          }
          fchdir(start_fd);
        }
      }
      close(start_fd);
    }

    return(success);
  }
