#ifndef __INTERFACE_ICHANGEABLE__
#define __INTERFACE_ICHANGEABLE__

#include <vector>
#include <stdexcept>

class IChangeableException : public std::exception
{
	const char * msg;
	public:
		IChangeableException(const char * message)
			: msg(message)
		{
		}

		const char * what() const noexcept override
		{
			return msg;
		}
};

/**
This interface allows not to redraw windows that often.
*/
class IChangeable
{
    private:
        // followin objects will also be notified about change
		IChangeable * parent;
		std::vector<IChangeable *> they_depend_on_me;
        bool up_to_date;
        
        virtual void ApplyChange() = 0;
    public:

		/**
		creates instance of class IChangeable with a provided parent
		@param parent instance of class IChangeable, which will be notified when something
		interesting changed in this window
		*/
        IChangeable(IChangeable * parent)
            :   parent(parent),
				up_to_date(false)
        {
        }

		virtual ~IChangeable() = default;

		/**
		applyes changes to this window if it isn't up to date
		*/
        void Commit()
        {
            if (!up_to_date)
			{
				ApplyChange();
				up_to_date = true;
			}
        }

		/**
		only sends notification to a parent
		*/
		void NotifyDependent()
		{
			if (parent)
				parent->NotifyChange();

			for (auto * dep : they_depend_on_me)
				dep->NotifyChange();
		}

		/**
		if IChangeable item was changed in the way it affects it's parent
		it'll notify the parent so it'll make appropriate reactions to this
		change in It's overriden ApplyChange() function
		*/
        void NotifyChange()
        {
            up_to_date = false;
			NotifyDependent();
        }

		/**
		Tells if window is up to date or it shall be updateds
		*/
        bool UpToDate() const
        {
            return up_to_date;
        }
		
		bool HasParent() const
		{
			return parent != nullptr;
		}

		void SetParent(IChangeable * new_parent)
		{
			if (HasParent())
				throw std::invalid_argument("can't set parent while has one");

			parent = new_parent;
		}

		void Free()
		{
			parent = nullptr;
		}

		IChangeable * GetParent() const
		{
			return parent;
		}

        void AddDependent(IChangeable * new_dependent)
        {
            they_depend_on_me.push_back(new_dependent);
        }

		void RemoveDependent(IChangeable * dependent)
		{
			for (size_t i = 0; i < they_depend_on_me.size(); i++)
			{
				if (they_depend_on_me[i] == dependent)
				{
					they_depend_on_me.erase(they_depend_on_me.begin() + i);				
					return;
				}
			}

			throw std::invalid_argument("dependent");
		}
};


#endif
